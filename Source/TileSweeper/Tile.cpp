// Copyright(c) Forge Reply. All Rights Reserved.

#include "Tile.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"


ATile::ATile()
{
	if (!IsValid(RootComponent))
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	}

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Game/Geometry/Meshes/ChamferBox"));
	MeshComponent->SetStaticMesh(CubeMesh.Object);
	MeshComponent->SetRelativeScale3D(FVector(2.0f, 2.0f, 1.0f));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> TimeMaterialInstance(TEXT("/Game/Materials/TileMaterialInstance"));
	MeshComponent->SetMaterial(0, TimeMaterialInstance.Object);
	MeshComponent->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}


void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent->SetVectorParameterValueOnMaterials(FName("TileBaseColor"), FVector(FColor::Silver));
	MeshComponent->SetScalarParameterValueOnMaterials(FName("TileEmission"), 0.0f);
}

void ATile::StepOn(bool realPlayerPress)
{
	MeshComponent->SetVectorParameterValueOnMaterials(FName("TileBaseColor"), FVector(ColorToSet));
	MeshComponent->SetScalarParameterValueOnMaterials(FName("TileEmission"), 1.0f);
}

void ATile::StepOff(bool realPlayerPress)
{
	MeshComponent->SetVectorParameterValueOnMaterials(FName("TileBaseColor"), FVector(FColor::Silver));
	MeshComponent->SetScalarParameterValueOnMaterials(FName("TileEmission"), 0.0f);
}



