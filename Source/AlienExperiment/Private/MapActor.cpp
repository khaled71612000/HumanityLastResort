// Fill out your copyright notice in the Description page of Project Settings.


#include "MapActor.h"
#include "Kismet/GameplayStatics.h"

AMapActor::AMapActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMapActor::BuildMap(const FVector CenterLocation, const int X, const int Y)
{
	//Dont Execute if maptiles already got tiles

	if (MapTiles.Num() == 0) {
		MapSize.X = 0;
		MapSize.Y = 0;
	

		for (int32 OuterIndex = 0; OuterIndex <= Y - 1; ++OuterIndex)
		{
			for (int32 InnerIndex = 0; InnerIndex <= X - 1; ++InnerIndex)
			{
				float SectorSize = 400.f;

				//Prepare Spawn Transform
				FVector SpawnLocation =
					FVector(static_cast<float>(InnerIndex) - static_cast<float>(X) / 2.f,
						static_cast<float>(OuterIndex) - static_cast<float>(X) / 2.f,
						0.f)
					* SectorSize
					* 1.f
					+ CenterLocation;
				FTransform SpawnTransform;
				SpawnTransform.SetLocation(SpawnLocation);

				if (CellClass.LoadSynchronous()) {
					AActor* TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
						this,
						CellClass.LoadSynchronous(),
						SpawnTransform);
					ACellActor* Tile = Cast< ACellActor>(TileToSpawn);
					if (Tile) {
						Tile->SetCellInfo(FBlankCellInfo(InnerIndex, OuterIndex, 0));
					}
					TileToSpawn->FinishSpawning(SpawnTransform);
					MapTiles.Add(TileToSpawn);
					TileToSpawn->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
				}
				
			}
		}
	}
}

void AMapActor::BeginPlay()
{
	Super::BeginPlay();
	
}



