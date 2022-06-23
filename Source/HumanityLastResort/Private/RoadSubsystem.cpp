// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadSubsystem.h"
#include "Road.h"


void URoadSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void URoadSubsystem::AddRoad(ARoad* Road)
{
	Roads.Add(Road);

	UpdateRoads();

}

void URoadSubsystem::UpdateRoads()
{
	for (ARoad* curRoad : Roads)
	{
		curRoad->UpdateSideOfRoadTile();
	}
}

void URoadSubsystem::RemoveRoad(ARoad* Road)
{
	Roads.Remove(Cast<ARoad>(Road));
}
