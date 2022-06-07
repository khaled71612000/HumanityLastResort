// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AlienSubsystem.generated.h"

/**
 *
 */
UCLASS()
class HUMANITYLASTRESORT_API UAlienSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	int32 NumOfAlienTypes = 4;
	TArray<class AAlien*> SpawnedAliens;
	TArray <TArray<class AAlien*>> AliensPool;

	int32 GlobalMood;
	int32 NumOfAliens;
	float GlobalMoodPercentage;

private:
	void Initialize(FSubsystemCollectionBase& Collection) override;
	TStatId GetStatId() const override;
	void Tick(float DeltaTime) override;
	void UpdateNumOfAliens(class AAlien* Alien);


public:
	void UpdateGlobalMood();
	UFUNCTION(BlueprintCallable)
	float GetGlobalMoodPercentage();
	UFUNCTION(BlueprintCallable)
	int32 GetNumOfAliens();
};
