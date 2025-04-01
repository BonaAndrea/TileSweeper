// Copyright(c) Forge Reply. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM()
enum class ETileType : uint8
{
	Normal,
	Green,
	Red,
	Blue
};


// Simple implementation of the Tile class.
// It consists in a platform sized 2m x 2m x 1m.
UCLASS(Abstract)
class TILESWEEPER_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATile();
protected:
	virtual void BeginPlay() override;

public:	
	// Method to call to notify when the player steps on this tile.
	// Ho aggiunto un parametro bool per sapere quando la casella
	// sta venendo illuminata tramite pressione della tile blu
	// ed evitare che questo venga registrato come pressione
	// dal giocatore. Il valore di default è in ogni caso
	// false, per la comodità di non dover esplicitare
	// il parametro in ogni altra chiamata.
	virtual void StepOn(bool realPlayerPress = false);

	// Method to call to notify when the player steps off this tile.
	// Come sopra, se lo StepOff è eseguito tramite pressione della
	// tile blu, allora la casella viene "rispenta".
	// Il valore di default è in ogni caso false,
	// per la comodità di non dover esplicitare il
	// parametro in ogni altra chiamata.
	virtual void StepOff(bool realPlayerPress = false);

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Visual, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;
	// variabile per registrare se la casella è già stata trovata
	bool hasBeenSteppedOn = false;
	FColor ColorToSet = FColor::Silver;

};
