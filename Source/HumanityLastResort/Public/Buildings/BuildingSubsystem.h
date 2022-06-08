// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BuildingSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API UBuildingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	int32 NumOfBuildings = 7;
public:
	TArray<TArray<class ABuilding*>> Buildings;
	void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintCallable)
	void AddBuilding(class APlaceable* Building);
	void RemoveBuilding(class APlaceable* Building);
};
