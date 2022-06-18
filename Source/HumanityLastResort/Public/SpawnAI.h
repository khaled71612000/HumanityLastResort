// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "SpawnAI.generated.h"

/**
 * 
 */

USTRUCT()
struct FAliens
{
	GENERATED_BODY()

		UPROPERTY()
		TArray<class AAlien*> AlienType;
};

UCLASS()
class HUMANITYLASTRESORT_API ASpawnAI : public AVolume
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:

	TArray<FAliens> AliensToSpawn;
	TArray<int32> SpawnAlienTypeInd;

	int32 NumOfAllAliensToSpawn = 20;
	int32 IndOfAlienToSpawn = 0;
	int32 NumOfAliensType = 4;
	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation;
	FRotator SpawnRotation;
	FVector SpawnScale;
	FTimerHandle SpawnManager;

	UPROPERTY(EditAnywhere, Category = "SpawnAlien")
	int32 InitialSpawnRate = 2;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<TSubclassOf<class AAlien>> Aliens;
	UPROPERTY()
	class UAlienSubsystem* AlienSubsystem;
	UPROPERTY()
	class AAlien* AlienToSpawn;

	void SpawnAnAlien();
	void SpawnAllAliens();
	UFUNCTION()
		void UpdateSpawnTimer(int32 SpawnRate);
};
