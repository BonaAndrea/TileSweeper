// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "NormalTile.generated.h"

/**
 * 
 */
UCLASS()
class ANormalTile : public ATile
{
	GENERATED_BODY()

protected:

	UPROPERTY(Transient)
	ETileType TileType = ETileType::Normal;

public:
	void StepOn(bool notRealPlayerPress = false) override;
	void StepOff(bool realPlayerPress = false) override;
};
