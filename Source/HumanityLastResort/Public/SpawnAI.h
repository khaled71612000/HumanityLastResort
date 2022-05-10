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

private:
	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation;
	FRotator SpawnRotation;
	virtual void BeginPlay() override;

	void SpawnAnAlien();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AAICharacterBase> ActorToSpawn;

public:
	UPROPERTY(EditAnywhere, Category = "Spawn")
		float SpawnRate = 8.f;
	
};
