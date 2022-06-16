// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadManager.h"
#include "Road.h"

void URoadManager::AddRoad(ARoad* RoadRef)
{
	RoadsTilesArray.Add(RoadRef);

	for (ARoad* curRoad : RoadsTilesArray) {
		curRoad->UpdateSideOfRoadTile();
	}
}
