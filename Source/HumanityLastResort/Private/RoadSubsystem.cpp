// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadSubsystem.h"
#include "Road.h"
#include "Placeable.h"



void URoadSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void URoadSubsystem::AddRoad(ARoad* RoadRef)
{
	Roads.Add(RoadRef);

	for (ARoad* curRoad : Roads) 
	{
		curRoad->UpdateSideOfRoadTile();
	}

}

void URoadSubsystem::RemoveRoad(APlaceable* Road)
{
	if (Cast<ARoad>(Road))
	{
		Roads.Remove(Cast<ARoad>(Road));
	}
}
