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
protected:
	void Initialize(FSubsystemCollectionBase& Collection) override;
public:
	UPROPERTY()
	TArray<class ARoad*> Roads;
	
	UFUNCTION(BlueprintCallable)
	void AddRoad(class ARoad* RoadRef);
	void RemoveRoad(class APlaceable* Road);

	//void RemoveRoad(ARoad* RoadRef);
};
