// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadSubsystem.h"
#include "Road.h"

void URoadSubsystem::AddRoad(ARoad* RoadRef)
{
	RoadsTilesArray.Add(RoadRef);

	for (ARoad* curRoad : RoadsTilesArray) {
		curRoad->UpdateSideOfRoadTile();
	}
}

//void URoadSubsystem::RemoveRoad(ARoad* RoadRef)
//{
//	if (ARoad* R = Cast<ARoad>(RoadRef))
//	{
//		RoadsTilesArray.Remove(R);
//	}
//}
