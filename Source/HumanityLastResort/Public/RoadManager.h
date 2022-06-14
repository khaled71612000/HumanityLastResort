// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RoadManager.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API URoadManager : public UWorldSubsystem
{
	GENERATED_BODY()

		TArray<class ARoad*> RoadsTilesArray;

		UFUNCTION(BlueprintCallable)
		void AddRoad(ARoad* RoadRef);
};
