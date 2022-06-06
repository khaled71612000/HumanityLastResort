// Fill out your copyright notice in the Description page of Project Settings.


#include "NewGrid.h"
#include "NewCell.h"

// Sets default values
ANewGrid::ANewGrid()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ANewGrid::PopulateGrid()
{
	float FullGridSize = GridSize * WorldGridSize;
	
	float WorldOffset = (FullGridSize * 0.5) - (WorldGridSize * 0.5);
	float WorldOffsetX = WorldOffset; 
	float WorldOffsetY = WorldOffset;
	FVector spawnPos;

	//Y loop
	for (float i = 0; i < GridSize - 1 ; i++)
	{
		//X loop
		for (float j = 0; j < GridSize - 1; j++)
		{

			WorldOffsetX = WorldGridSize * j - WorldOffset;
			WorldOffsetY = WorldGridSize * i - WorldOffset;

			spawnPos = FVector(WorldOffsetX, WorldOffsetY, 0.f);

			//For Debugging 
			/*ANewCell* temp = GetWorld()->SpawnActor<ANewCell>(ActorToSpawn, spawnPos,
				GetActorRotation());*/

			GridPoints.Add(spawnPos);
		}
	}
}

FVector ANewGrid::GetClosestPosition(FVector InPosition)
{
	
	closestPos = GridPoints[0];
	
	closestDistance = FVector::Dist(closestPos, InPosition);

	for (FVector element : GridPoints)
	{
		if (FVector::Dist(element, InPosition) < closestDistance) {
			closestPos = element;
			closestDistance = FVector::Dist(element, InPosition);
		}

	}

	return closestPos;
}

void ANewGrid::PreSave(const class ITargetPlatform* TargetPlatform)
{
	Super::PreSave(TargetPlatform);
	//GET SIZE OF MESH

}

// Called when the game starts or when spawned
void ANewGrid::BeginPlay()
{
	Super::BeginPlay();
	PopulateGrid();
}

// Called every frame
void ANewGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

