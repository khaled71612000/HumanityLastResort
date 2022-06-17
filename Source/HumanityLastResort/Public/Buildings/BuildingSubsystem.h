// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BuildingSubsystem.generated.h"

/**
 * 
 */

USTRUCT()
struct FBuildingArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<class ABuilding*> buildings;
};

UCLASS()
class HUMANITYLASTRESORT_API UBuildingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	int32 NumOfBuildings = 7;

public:
	UPROPERTY()
	TArray<FBuildingArray> Buildings;

	void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintCallable)
	void AddBuilding(class ABuilding* Building);
	void RemoveBuilding(class ABuilding* Building);
};
