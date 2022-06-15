// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadSubsystem.h"
#include "Road.h"

void URoadSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void URoadSubsystem::AddRoad(APlaceable* Road)
{
	if (Cast<ARoad>(Road))
	{
		Roads.Add(Cast<ARoad>(Road));
	}
}

void URoadSubsystem::RemoveRoad(APlaceable* Road)
{
	if (Cast<ARoad>(Road))
	{
		Roads.Remove(Cast<ARoad>(Road));
	}
}
