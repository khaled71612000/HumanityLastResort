// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"
#include "Components/StaticMeshComponent.h"

ARoad::ARoad()
{
	PathWayNorth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PathWayNorth"));
	PathWayEast = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PathWayEast"));
	PathWaySouth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PathWaySouth"));
	PathWayWest = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PathWayWest"));

}

void ARoad::BeginPlay()
{
}

void ARoad::OnNewRoadTileAdded()
{

}
