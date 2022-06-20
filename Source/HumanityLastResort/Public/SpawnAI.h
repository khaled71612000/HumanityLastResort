// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "SpawnAI.generated.h"

/**
 *
 */

USTRUCT(Blueprintable)
struct FAliens
{
	GENERATED_BODY()

		UPROPERTY()
		TArray<class AAlien*> AlienType;
};

UCLASS(Blueprintable)
class HUMANITYLASTRESORT_API ASpawnAI : public AVolume
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:

	TArray<FAliens> AliensToSpawn;
	TArray<int32> SpawnAlienTypeInd;

	int32 NumOfAllAliensToSpawn = 100;
	int32 IndOfAlienToSpawn = 0;
	int32 NumOfAliensType = 4;

	void SpawnAllAliens();
	void InitAlien(class AAlien* Alien);
	void InitAlienComponents(class AAlien* Alien);

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "SpawnAlien")
	void OnSpawning();

private:
	UPROPERTY(EditAnywhere, Category = "SpawnAlien")
		int32 InitialSpawnRate = 8;

	UPROPERTY()
		class UAlienSubsystem* AlienSubsystem;
	UPROPERTY()
		class AAlien* AlienToSpawn;

	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation;
	FRotator SpawnRotation;
	FVector SpawnScale;

	FTimerHandle SpawnManager;
	UFUNCTION()
	void UpdateSpawnTimer(int32 SpawnRate);
	void SpawnAnAlien();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<TSubclassOf<class AAlien>> Aliens;

};
