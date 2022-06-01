// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/NeedSatisfactionTask.h"
#include "Resting.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API UResting : public UNeedSatisfactionTask
{
	GENERATED_BODY()

public:
	void Satisfy(class AAlien* Alien, class UNeedComponent* Need) override;
	class AHotel* GetHotel();
	void MoveToHotel(class AHotel* Hotel);
};
