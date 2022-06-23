// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NeedSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API UNeedSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
	void Initialize(FSubsystemCollectionBase& Collection) override;
	int32 NumOfNeeds = 7;
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<int32> NeedsStats;

	void IncrementNeed(int32 NeedIndex);
	void DecrementNeed(int32 NeedIndex);
};
