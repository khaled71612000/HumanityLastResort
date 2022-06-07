// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BuildingSubsystem.h"
#include "Building.h"

void UBuildingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Buildings.SetNum(NumOfBuildings);
}

void UBuildingSubsystem::AddBuilding(APlaceable* Building)
{
	if (ABuilding* Build = Cast<ABuilding>(Building))
	{
		Buildings[Build->BuildingType].Add(Build);
	}
	
}

void UBuildingSubsystem::RemoveBuilding(APlaceable* Building)
{
	if (ABuilding* Build = Cast<ABuilding>(Building))
	{
		Buildings[Build->BuildingType].Remove(Build);

	}
}
