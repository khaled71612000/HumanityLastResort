// Fill out your copyright notice in the Description page of Project Settings.

#include "Building.h"
#include "Components/SphereComponent.h"
#include "Economy/EconomySubsystem.h"
#include "SelectionSubsystem.h"


ABuilding::ABuilding() 
{
	CurOccupants = 0;
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	world = GetWorld();
	EconomySubsystem = world->GetSubsystem<UEconomySubsystem>();
	SelectionSubSystem = world->GetSubsystem<USelectionSubsystem>();
	SelectionSubSystem->RegisterSelectionHandler(Cast<IISelectionHandler>(this));
}

void ABuilding::AddProfit()
{
	EconomySubsystem->AddCash(Profit);
}

void ABuilding::SubtractLoss()
{
	EconomySubsystem->SubtractCash(Loss);
}


APlaceable* ABuilding::Selected(const FHitResult& selectionInfoRay)
{
	return this;
}

void ABuilding::HightLight()
{
	SkeletalMeshComponent->SetScalarParameterValueOnMaterials(TEXT("Selected"), 1);

}
void ABuilding::DeHighLight()
{
	SkeletalMeshComponent->SetScalarParameterValueOnMaterials(TEXT("Selected"), 0);
}
