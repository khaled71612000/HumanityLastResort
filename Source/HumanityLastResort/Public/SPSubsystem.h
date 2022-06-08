// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SPSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API USPSubsystem : public UWorldSubsystem 
{
	GENERATED_BODY()
public:
	
	UFUNCTION()
		void OnLeftMouseRelease();
	
};
