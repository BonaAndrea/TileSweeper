// Fill out your copyright notice in the Description page of Project Settings.


#include "GreenTile.h"

void AGreenTile::StepOn(bool notRealPlayerPress)
{
	Super::StepOn();
	MeshComponent->SetVectorParameterValueOnMaterials(FName("TileBaseColor"), FVector(ColorToSet));  // Colore verde
	if(!notRealPlayerPress)
	{
		hasBeenSteppedOn = true;
	}
}

void AGreenTile::StepOff(bool notRealPlayerPress)
{
	if(!notRealPlayerPress || hasBeenSteppedOn) return;
	Super::StepOff();
}