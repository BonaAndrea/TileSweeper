// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "BlueTile.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTileStateChanged, bool, bIsTileActive);

UCLASS()
class ABlueTile : public ATile
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(Transient)
	ETileType TileType = ETileType::Blue;
	FColor ColorToSet = FColor::Blue;
public:
	void StepOn(bool realPlayerPress = false);
	void StepOff(bool realPlayerPress = false);
	FOnTileStateChanged OnTileStateChanged;
};
