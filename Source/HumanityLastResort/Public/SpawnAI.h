// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "SpawnAI.generated.h"

/**
 * 
 */


UCLASS()
class HUMANITYLASTRESORT_API ASpawnAI : public AVolume
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

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

	FTimerHandle SpawnManager;
	UFUNCTION()
	void UpdateSpawnTimer(int32 SpawnRate);
	void SpawnAnAlien();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class AAlien>> Aliens;

};
