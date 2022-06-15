// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NeedSatisfactionTask.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API UNeedSatisfactionTask : public UObject
{
	GENERATED_BODY()

private:
	class AAlien* CurAlien;
	class UNeedComponent* CurNeed;
	class ABuilding* CurBuilding;
	int32 CurBuildingType;
	float CurTaskTime;
	FTimerHandle TaskTimeManager;


	class UBuildingSubsystem* BuildingSubsystem;
	class URoadSubsystem* RoadSubsystem;
	class UNavigationSystemV1* NavArea;


public:
	void CustomBeginPlay();
	bool TrySatisfy(class UNeedComponent* Need, class AAlien* Alien);
	void Satisfy();
	bool CheckAccessibility(FVector Start, FVector End);
	void Wait();
	void DoTask();
	void SatisfiedAlien();
	void Wander(class AAlien* Alien);

};

