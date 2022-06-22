// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AlienSubsystem.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnRateUpdate, int32, SpawnRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOver);


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

	int32 GlobalMood = 70;
	int32 NumOfAliens;
	float SpawnMultiplier = 1;
	UPROPERTY(BlueprintAssignable)
	FSpawnRateUpdate SpawnRateUpdate;

	UPROPERTY(BlueprintAssignable)
	FGameOver GameOver;

private:
	void Initialize(FSubsystemCollectionBase& Collection) override;
	TStatId GetStatId() const override;
	void Tick(float DeltaTime) override;

public:
	void MoveAlienToPool(class AAlien* Alien);
	void UpdateGlobalMood(int32 Amount);
	UFUNCTION(BlueprintCallable)
		int32 GetGlobalMood();
	UFUNCTION(BlueprintCallable)
		int32 GetNumOfAliens();

};
