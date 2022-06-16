// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AlienSubsystem.generated.h"

/**
 *
 */

USTRUCT()
struct FAliensArray
{
	GENERATED_BODY()
	TArray<class AAlien*> Aliens;
};

UCLASS()
class HUMANITYLASTRESORT_API UAlienSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	int32 NumOfAlienTypes = 4;
	UPROPERTY()
	TArray<class AAlien*> SpawnedAliens;

	UPROPERTY()
	TArray <FAliensArray> AliensPool;

	int32 GlobalMood;
	int32 NumOfAliens;
	int32 GlobalMoodPercentage;

	int32 SpawnRate = 5;

private:
	void Initialize(FSubsystemCollectionBase& Collection) override;
	TStatId GetStatId() const override;
	void Tick(float DeltaTime) override;
	void SubtractAlienInfo(class AAlien* Alien);
	void UpdateSpawningRate();

public:
	void UpdateGlobalMood(int32 Amount);
	void UpdateGlobalMoodPercentage();
	UFUNCTION(BlueprintCallable)
		int32 GetGlobalMoodPercentage();
	UFUNCTION(BlueprintCallable)
		int32 GetNumOfAliens();
};
