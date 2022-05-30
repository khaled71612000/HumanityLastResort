// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EconomySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API UEconomySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
	int32 Cash;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
public:
	void AddCash(int32 Amount);
	void SubtractCash(int32 Amount);
};
