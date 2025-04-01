// Copyright(c) Forge Reply. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TileSweeperGameMode.generated.h"

class ATile;
UCLASS(minimalapi)
class ATileSweeperGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void HandleTileStateChanged(bool bIsTileActive);

	
public:
	ATileSweeperGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Resets the game, by forcing the reload of the game level.
	void ResetGame();

	// Returns the total number of Green Tiles in the tile grid.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetTotalGreenTiles();

	// Returns the number of Green Tiles that the player found.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetGreenTilesFound();

	// Returns the total number of Red Tiles in the tile grid.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetTotalRedTiles();

	// Returns the number of Red Tiles that the player found.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetRedTilesFound();


	// Funzione generica che accetta una mappa di (coordinate, Tilemap)
	// e itera su questa, restituendo quante di quelle caselle
	// abbiano il flag hasBeenSteppedOn a True
	int32 GetTilesFound(const TMap<FIntPoint, ATile*>& TileMap) const;

	// Returns the distance from the player to the closest Green Tile (that the player has not found yet).
	// Returns -1 if all Green Tiles have been found.
	// Distance is defined as the number of tiles that the player has to move (horizontally and vertically)
	// to reach the closest Green Tile.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetClosestGreenTileDistance();

	// Returns the distance from the player to the closest Red Tile (that the player has not found yet).
	// Returns -1 if all Red Tiles have been found.
	// Distance is defined as the number of tiles that the player has to move (horizontally and vertically)
	// to reach the closest Red Tile.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Game)
	int32 GetClosestRedTileDistance();

	// Funzione generica che accetta una collezione di Tile e ritorna quella più vicina al giocatore
	int32 GetClosestTileDistance(const TMap<FIntPoint, ATile*>& TileMap, int32 TilesFound, int32 TotalTiles) const;

	// Defines the size of the tile grid to generate.
	// Must be at least 3.
	// Can be changed in the "TileGameModeBP" blueprint.
	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	int32 TileGridSize = 10;

	// Defines the number of Green Tiles to randomly place in the tile grid.
	// Must be at least 1.
	// Can be changed in the "TileGameModeBP" blueprint.
	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	int32 GreenTilesToSpawn = 5;

	// Defines the number of Red Tiles to randomly place in the tile grid.
	// Must be at least 1.
	// Can be changed in the "TileGameModeBP" blueprint.
	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	int32 RedTilesToSpawn = 5;

	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	TSubclassOf<class ATile> TileClass;

	// Funzione chiamata da BlueTile.cpp
	// che mostra temporaneamente la posizione
	// di tutte le caselle verdi
	void ToggleGreenTilesShow(bool stepOn);

private:
TMap<FIntPoint, ATile*> Tiles;

	TMap<FIntPoint, ATile*> RedTiles;
	TMap<FIntPoint, ATile*> GreenTiles;

	AActor* PlayerCharacter;
	ACharacter* Character;
	float TileSize = 200.0f;
	int CurrentX = 0;
	int CurrentY = 0;
	int GreenTilesCount = 0;
	int RedTilesCount = 0;
	class ATileHUD* TileHUD;
	FTimerHandle EndScreenTimerHandle;
};



