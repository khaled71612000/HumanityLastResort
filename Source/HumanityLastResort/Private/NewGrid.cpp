// Fill out your copyright notice in the Description page of Project Settings.


#include "NewGrid.h"
#include "NewCell.h"

// Sets default values
ANewGrid::ANewGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	for (float i = 0; i < GridSize -1 ; i++)
	{
		//X loop
		for (float j = 0; j < GridSize - 1; j++)
		{


			WorldOffsetX = WorldGridSize * j - WorldOffset;
			WorldOffsetY = WorldGridSize * i - WorldOffset;

			spawnPos = FVector(WorldOffsetX, WorldOffsetY, 0.f);


			ANewCell* temp = GetWorld()->SpawnActor<ANewCell>(ActorToSpawn, spawnPos,
				GetActorRotation());

			GridArray.Add(temp);
		}
	}
}

FVector ANewGrid::GetClosestPosition(FVector InPosition)
{
	
	closestPos = GridArray[0]->GetActorLocation();
	
	closestDistance = FVector::Dist(closestPos, InPosition);

	for (AActor* element : GridArray)
	{
		element->GetActorLocation();
		if (FVector::Dist(element->GetActorLocation(), InPosition) < closestDistance) {
			closestPos = element->GetActorLocation();
			closestDistance = FVector::Dist(element->GetActorLocation(), InPosition);
		}

	}

	return closestPos;
}

void ANewGrid::PreSave(const class ITargetPlatform* TargetPlatform)
{

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

