// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadSubsystem.h"
#include "Road.h"

void URoadSubsystem::AddRoad(ARoad* RoadRef)
{
	RoadsTilesArray.Add(RoadRef);

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
