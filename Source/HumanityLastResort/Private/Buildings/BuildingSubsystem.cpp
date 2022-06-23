// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BuildingSubsystem.h"
#include "Building.h"

void UBuildingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Buildings.SetNum(NumOfBuildings);
}

void UBuildingSubsystem::AddBuilding(ABuilding* Building)
{
	Buildings[Building->BuildingType].buildings.Add(Building);
}

void UBuildingSubsystem::RemoveBuilding(ABuilding* Building)
{
	Buildings[Building->BuildingType].buildings.Remove(Building);
}
