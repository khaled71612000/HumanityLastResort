// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "SpawnAI.generated.h"

/**
 * 
 */
UCLASS()
class ALIENEXPERIMENT_API ASpawnAI : public AVolume
{
	GENERATED_BODY()

private:
	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation;
	FRotator SpawnRotation;
private:
	virtual void BeginPlay() override;

	void SpawnAnAlien();
};
