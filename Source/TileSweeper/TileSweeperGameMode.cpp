// Copyright(c) Forge Reply. All Rights Reserved.

#include "TileSweeperGameMode.h"

#include "BlueTile.h"
#include "TileSweeperCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Tile.h"
#include "Kismet/GameplayStatics.h"
#include "TileHUD.h"
#include "GreenTile.h"
#include "NormalTile.h"
#include "RedTile.h"
#include "GameFramework/CharacterMovementComponent.h"


ATileSweeperGameMode::ATileSweeperGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
}

void ATileSweeperGameMode::ResetGame()
{
	UGameplayStatics::OpenLevel(this, FName("/Game/Levels/LoadingLevel"));
}

int32 ATileSweeperGameMode::GetTotalGreenTiles()
{
	return GreenTiles.Num();
}

int32 ATileSweeperGameMode::GetGreenTilesFound()
{
	return GetTotalGreenTiles() - GreenTilesCount;
}

int32 ATileSweeperGameMode::GetTotalRedTiles()
{
	return RedTiles.Num();
}

int32 ATileSweeperGameMode::GetRedTilesFound()
{
	return GetTotalRedTiles() - RedTilesCount;
}

int32 ATileSweeperGameMode::GetTilesFound(const TMap<FIntPoint, ATile*>& TileMap) const
{
	int Count = 0;

	for (const TPair<FIntPoint, ATile*>& Pair : TileMap)
	{
		ATile* Tile = Pair.Value; 
    
		if (Tile && Tile->hasBeenSteppedOn)
		{
			Count++;
		}
	}
    
	return Count;
}

int32 ATileSweeperGameMode::GetClosestGreenTileDistance()
{
	return GetClosestTileDistance(GreenTiles, GetGreenTilesFound(), GreenTiles.Num());
}

int32 ATileSweeperGameMode::GetClosestRedTileDistance()
{
	return GetClosestTileDistance(RedTiles, GetRedTilesFound(), RedTiles.Num());
}

int32 ATileSweeperGameMode::GetClosestTileDistance(const TMap<FIntPoint, ATile*>& TileMap, int32 TilesFound, int32 TotalTiles) const
{
	if (TileMap.Num() == 0 || TilesFound == TotalTiles)
	{
		// Nessuna casella valida disponibile
		return -1; 
	}

	// Inizializzazione con valore massimo
	int MinDistance = TNumericLimits<int>::Max(); 
	bool bFoundValidTile = false;

	for (const TPair<FIntPoint, ATile*>& Pair : TileMap)
	{
		ATile* Tile = Pair.Value;
		// Considero solo le caselle non ancora calpestate
		if (Tile && !Tile->hasBeenSteppedOn) 
		{
			int Distance = FMath::Abs(CurrentX - Pair.Key.X) + FMath::Abs(CurrentY - Pair.Key.Y);

			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				bFoundValidTile = true;
			}
		}
	}

	return bFoundValidTile ? MinDistance : -1;
}

void ATileSweeperGameMode::ToggleGreenTilesShow(bool stepOn)
{
	for (const TPair<FIntPoint, ATile*>& Pair : GreenTiles)
	{
		ATile* Tile = Pair.Value; 
    
		if (Tile)
		{
			if(stepOn)
			Tile->StepOn(true);
			else
			{
				Tile->StepOff(true);
			}
		}

	}
}

void ATileSweeperGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    PlayerCharacter = Cast<ATileSweeperCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
    TileHUD = Cast<ATileHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	Character = Cast<ACharacter>(PlayerCharacter);
	// Check sui parametri di inizializzazione del gioco
	if(TileGridSize < 3 || GreenTilesToSpawn < 1 || RedTilesToSpawn < 1)
	{
		UE_LOG(LogTemp, Error, TEXT("Parametri di inizializzazione errati!"));
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			UKismetSystemLibrary::QuitGame(GetWorld(), PC, EQuitPreference::Quit, false);
		}
	}
	
    FVector StartLocation(0.0f, 0.0f, -50.0f);
    FRotator Rotation(0.0f, 0.0f, 0.0f);

	// Ottengo le coordinate minime e massime dalla dimensione della griglia
    int tileEdges = TileGridSize / 2;

	// Creo un array di coppie di interi con le posizioni disponibili
	TArray<FIntPoint> AvailablePositions;
    for (int x = -tileEdges; x <= tileEdges; x++)
    {
        for (int y = -tileEdges; y <= tileEdges; y++)
        {
        	// escludendo (0,0) che nel nostro caso è una casella preesistente dove spawna il giocatore
            if (!(x == 0 && y == 0))
            {
                AvailablePositions.Add(FIntPoint(x, y));
            }
        }
    }

    // Per introdurre della randomicità, mischio le posizioni nel vettore
    for (int i = AvailablePositions.Num() - 1; i > 0; i--)
    {
        int32 SwapIndex = FMath::RandRange(0, i);
        AvailablePositions.Swap(i, SwapIndex);
    }
    
    int TotalSpecialTiles = RedTilesToSpawn + GreenTilesToSpawn;
	bool bSpawnedBlueTile = false;
	
    // Spawn delle tile nel gioco. Avendo mischiato le posizioni disponibili nel vettore
	// AvailablePositions prima, posso iterare semplicemente e creare volta per volta
	// prima le rosse, poi le verdi, poi una blu e infine le rimanenti
    for (int i = 0; i < AvailablePositions.Num(); i++)
    {
        FIntPoint TileCoord = AvailablePositions[i];
        FVector SpawnLocation = StartLocation + FVector(TileCoord.X * TileSize, TileCoord.Y * TileSize, 0.0f);
        ATile* SpawnedTile = nullptr;

        if (i < RedTilesToSpawn)
        {
            SpawnedTile = GetWorld()->SpawnActor<ARedTile>(ARedTile::StaticClass(), SpawnLocation, Rotation);
            RedTiles.Add(TileCoord, Cast<ARedTile>(SpawnedTile));
        }
        else if (i < TotalSpecialTiles)
        {
            SpawnedTile = GetWorld()->SpawnActor<AGreenTile>(AGreenTile::StaticClass(), SpawnLocation, Rotation);
            GreenTiles.Add(TileCoord, Cast<AGreenTile>(SpawnedTile));
        }
    	else if(!bSpawnedBlueTile)
    	{
    		SpawnedTile = GetWorld()->SpawnActor<ABlueTile>(ABlueTile::StaticClass(), SpawnLocation, Rotation);
    		bSpawnedBlueTile = true;
			ABlueTile* BlueTile = static_cast<ABlueTile*>(SpawnedTile);
    		BlueTile->OnTileStateChanged.AddDynamic(this, &ATileSweeperGameMode::HandleTileStateChanged);
    	}
        else
        {
            SpawnedTile = GetWorld()->SpawnActor<ANormalTile>(ANormalTile::StaticClass(), SpawnLocation, Rotation);
        }

        if (SpawnedTile)
        {
            Tiles.Add(TileCoord, SpawnedTile);
        }
    }

	GreenTilesCount = GreenTiles.Num();
	RedTilesCount = RedTiles.Num();
	
}

void ATileSweeperGameMode::HandleTileStateChanged(bool bIsTileActive)
{
	if (bIsTileActive)
	{
		// Esegui azioni quando la tile viene attivata (es. mostrare le tile verdi)
		ToggleGreenTilesShow(true);
	}
	else
	{
		// Esegui azioni quando la tile viene disattivata
		ToggleGreenTilesShow(false);
	}
}

void ATileSweeperGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerCharacter)
	{
		return;
	}

	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	int NewX = FMath::RoundToInt(PlayerLocation.X / TileSize);
	int NewY = FMath::RoundToInt(PlayerLocation.Y / TileSize);
	int tileEdges = TileGridSize / 2;

	// Reset della partita se una delle coordinate del giocatore
	// va oltre i bordi consentiti
	if (PlayerLocation.Z < -200.f)
	{
		ResetGame();
		return;
	}

	// Aggiorno le coordinate del giocatore se è cambiata la sua posizione
	if (NewX != CurrentX || NewY != CurrentY)
	{
		FIntPoint OldKey(CurrentX, CurrentY);
		FIntPoint NewKey(NewX, NewY);
		
		if(PlayerCharacter){
		
			// StepOff della vecchia tile
			if (Tiles.Contains(OldKey))
			{
				Tiles[OldKey]->StepOff();
			}



			if(!(Character && !Character->GetCharacterMovement()->IsFalling())) return;
			// Aggiornamento della posizione attuale
			CurrentX = NewX;
			CurrentY = NewY;
		
			// StepOn della nuova casella
			if (Tiles.Contains(NewKey))
			{
				if(!Tiles[NewKey]->hasBeenSteppedOn)
				{
					if (dynamic_cast<AGreenTile*>(Tiles[NewKey])) {
						GreenTilesCount--;
					} else if (dynamic_cast<ARedTile*>(Tiles[NewKey])){
						RedTilesCount--;
					}
				}
				Tiles[NewKey]->StepOn();
			}

			// Se il giocatore ha trovato tutte le caselle rosse
			// o tutte le caselle verdi, la partita è terminata
			if (GetGreenTilesFound() == GreenTiles.Num() || GetRedTilesFound() == RedTiles.Num())
			{
				if (TileHUD)
				{
					TileHUD->ShowEndScreen();

					// Timer per resettare il gioco dopo 5 secondi.
					// L'implementazione avviene tramite una lambda
					// function per evitare la definizione di una funzione
					// che avrebbe come unico scopo la chiamata di
					// ResetGame
					GetWorld()->GetTimerManager().SetTimer(
						EndScreenTimerHandle, 
						[this]() { ResetGame(); }, 
						5.0f, 
						false
					);
				}
			}
		}
	}
}

