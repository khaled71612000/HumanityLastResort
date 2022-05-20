// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AlienAIController.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API AAlienAIController : public AAIController
{
	GENERATED_BODY()

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

};
