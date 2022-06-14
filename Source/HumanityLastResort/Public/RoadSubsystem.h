// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RoadSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API URoadSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	TArray<class ARoad*>  RoadsTilesArray;

	UFUNCTION(BlueprintCallable)
	void AddRoad(ARoad* RoadRef);

	//void RemoveRoad(ARoad* RoadRef);
};
