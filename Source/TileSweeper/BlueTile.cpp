// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueTile.h"
#include "TileSweeperGameMode.h"

void ABlueTile::BeginPlay()
{
	Super::BeginPlay();
}

void ABlueTile::StepOn(bool realPlayerPress)
{
	Super::StepOn();
	MeshComponent->SetVectorParameterValueOnMaterials(FName("TileBaseColor"), FVector(ColorToSet));
	// Invia l'evento (notifica gli ascoltatori)
	OnTileStateChanged.Broadcast(true);  // true indica che la tile è attiva
}

void ABlueTile::StepOff(bool realPlayerPress)
{
	Super::StepOff();
	OnTileStateChanged.Broadcast(false);  // false indica che la tile è disattiva
}
