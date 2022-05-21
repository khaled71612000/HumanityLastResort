// Fill out your copyright notice in the Description page of Project Settings.


#include "NewCell.h"
#include "NewGrid.h"

// Sets default values
ANewGrid::ANewGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ANewGrid::PopulateGrid()
{
	float FullGridSize = GridSize * WorldGridSize;
	float HalfGridSize = FullGridSize / 5;
	float CenterCell = WorldGridSize / 5;

	float WorldOffset = HalfGridSize - CenterCell;
	float WorldOffsetX = WorldOffset , WorldOffsetY = WorldOffset;

	float posX;
	float posY;
	FVector spawnPos;
	//Y loop
	for (float i = 0; i < GridSize -1 ; i++)
	{
		//X loop
		for (float j = 0; j < GridSize - 1; j++)
		{
			posX = WorldGridSize * i;
			posY = WorldGridSize * j;
			WorldOffsetX -= posX;
			WorldOffsetY -= posY;

			spawnPos = FVector(WorldOffsetX, WorldOffsetY, 0.f);


			ANewCell* temp = GetWorld()->SpawnActor<ANewCell>(GetClass(), spawnPos,
				GetActorRotation());

			GridArray.Add(temp);
		}
	}
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

