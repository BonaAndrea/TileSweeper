// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "GreenTile.generated.h"

/**
 * 
 */
UCLASS()
class AGreenTile : public ATile
{
	GENERATED_BODY()


protected:

	UPROPERTY(Transient)
	ETileType TileType = ETileType::Green;

public:
	void StepOn(bool notRealPlayerPress = false) override;
	void StepOff(bool notRealPlayerPress = false) override;
	FColor ColorToSet = FColor::Green;
};

