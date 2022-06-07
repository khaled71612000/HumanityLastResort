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
public:
	UPROPERTY(EditAnywhere, Category = "SpawnAlien")
		float SpawnRate = 8.f;

	class UAlienSubsystem* AlienSubsystem;
private:
	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation;
	FRotator SpawnRotation;
	virtual void BeginPlay() override;

	void SpawnAnAlien();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<TSubclassOf<class AAlien>> Aliens;


};
