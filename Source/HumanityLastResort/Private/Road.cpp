// Fill out your copyright notice in the Description page of Project Settings.


#include "Road.h"
#include "Components/StaticMeshComponent.h"
#include "SelectionSubsystem.h"

ARoad::ARoad()
{
	PathWayWest = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PathWayWest"));
	PathWayWest->AttachTo(SceneComponent);
	PathWayWest->AddRelativeLocation(FVector(180, 0, 20));
	PathWayWest->AddRelativeRotation(FRotator(0, 0, 0));
	PathWayWest->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PathWayWest->SetCollisionProfileName(TEXT("NoCollision"));

	PathWayEast = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PathWayEast"));
	PathWayEast->AttachTo(SceneComponent);
	PathWayEast->AddRelativeLocation(FVector(-180, 0, 20));
	PathWayEast->AddRelativeRotation(FRotator(0, 0, -180));
	PathWayEast->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PathWayEast->SetCollisionProfileName(TEXT("NoCollision"));

	PathWayNorth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PathWayNorth"));
	PathWayNorth->AttachTo(SceneComponent);
	PathWayNorth->AddRelativeLocation(FVector(0, 180, 20));
	PathWayNorth->AddRelativeRotation(FRotator(0, -90, 0));
	PathWayNorth->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PathWayNorth->SetCollisionProfileName(TEXT("NoCollision"));

	PathWaySouth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PathWaySouth"));
	PathWaySouth->AttachTo(SceneComponent);
	PathWaySouth->AddRelativeLocation(FVector(0, -180, 20));
	PathWaySouth->AddRelativeRotation(FRotator(0, 90, 0));
	PathWaySouth->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PathWaySouth->SetCollisionProfileName(TEXT("NoCollision"));


}

void ARoad::BeginPlay()
{
	Super::BeginPlay();
	world = GetWorld();
	RoadStartRayLoc = GetActorLocation();
	RoadEndRayNorthLoc = RoadStartRayLoc + FVector(230,0,0);
	RoadEndRaySouthLoc = RoadStartRayLoc + FVector(-230, 0, 0);
	RoadEndRayEastLoc = RoadStartRayLoc + FVector(0, 230, 0);
	RoadEndRayWestLoc = RoadStartRayLoc + FVector(0, -230, 0);
}

void ARoad::UpdateSideOfRoadTile()
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	bool bHit;

	 bHit = world->LineTraceSingleByChannel(Hit, RoadStartRayLoc, RoadEndRayNorthLoc, ECC_Visibility, TraceParams);

	if (Hit.GetActor()) {
		PathWayWest->SetVisibility(false);
	}
	else {
		PathWayWest->SetVisibility(true);
	}

	 bHit = world->LineTraceSingleByChannel(Hit, RoadStartRayLoc, RoadEndRaySouthLoc, ECC_Visibility, TraceParams);

	if (Hit.GetActor()) {
		PathWayEast->SetVisibility(false);
	}
	else {
		PathWayEast->SetVisibility(true);
	}

	bHit = world->LineTraceSingleByChannel(Hit, RoadStartRayLoc, RoadEndRayEastLoc, ECC_Visibility, TraceParams);

	if (Hit.GetActor()) {
		PathWayNorth->SetVisibility(false);
	}
	else {
		PathWayNorth->SetVisibility(true);
	}

	bHit = world->LineTraceSingleByChannel(Hit, RoadStartRayLoc, RoadEndRayWestLoc, ECC_Visibility, TraceParams);

	if (Hit.GetActor()) {
		PathWaySouth->SetVisibility(false);
	}
	else {
		PathWaySouth->SetVisibility(true);
	}
}

