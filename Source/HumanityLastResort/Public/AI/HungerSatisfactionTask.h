// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/NeedSatisfactionTask.h"
#include "TimerManager.h"
#include "HungerSatisfactionTask.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API UHungerSatisfactionTask : public UNeedSatisfactionTask
{
	GENERATED_BODY()

public:
	void Satisfy(class AAlien* Alien, class UNeedComponent* Need) override;
	void Wait() override;
	class AResturant* GetResturant();
	void MoveToResturant(class AResturant* Resturant);
	void Eat();

private:
	float EatingTime;
	FTimerHandle EatingTimeManager;
	class AAlien* CurrentAlien;
	class UNeedComponent* Hunger;
};
