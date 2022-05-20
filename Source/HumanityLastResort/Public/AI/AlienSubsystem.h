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
	TArray<class AAlien*> Aliens;

private:
	TStatId GetStatId() const override;
	void Tick(float DeltaTime) override;
};
