// Fill out your copyright notice in the Description page of Project Settings.


#include "RedTile.h"


void ARedTile::StepOn(bool realPlayerPress)
{
	Super::StepOn();
	hasBeenSteppedOn = true;
	MeshComponent->SetVectorParameterValueOnMaterials(FName("TileBaseColor"), FVector(ColorToSet)); 
}

void ARedTile::StepOff(bool realPlayerPress)
{

}