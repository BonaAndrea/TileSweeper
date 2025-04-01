// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "RedTile.generated.h"

/**
 * 
 */
UCLASS()
class ARedTile : public ATile
{
	GENERATED_BODY()


protected:

	UPROPERTY(Transient)
	ETileType TileType = ETileType::Red;
	FColor ColorToSet = FColor::Red;

public:
	void StepOn(bool realPlayerPress = false) override;
	void StepOff(bool realPlayerPress = false) override;
	
};
