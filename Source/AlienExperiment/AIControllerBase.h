// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
//#include "AICharacterBase.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class ALIENEXPERIMENT_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
private:
	int TaskToPerformIndex;
	float HighPriority;
	float TaskPriority;

public:
	void ArrangeHotelsArray();
	void ArrangeResturantsArray();

	int GetTaskToPerform();
	void PerformTask();
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
