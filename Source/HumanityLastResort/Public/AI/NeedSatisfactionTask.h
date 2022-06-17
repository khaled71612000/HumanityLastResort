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
	UPROPERTY()
	class AAlien* CurAlien;
	UPROPERTY()
	class UNeedComponent* CurNeed;
	UPROPERTY()
	class ABuilding* CurBuilding;
	int32 CurBuildingType;
	float CurTaskTime;
	FTimerHandle TaskTimeManager;
	UPROPERTY()
	class UBuildingSubsystem* BuildingSubsystem;
	UPROPERTY()
	class URoadSubsystem* RoadSubsystem;
	UPROPERTY()
	class UNavigationSystemV1* NavArea;
	UPROPERTY()
	class ATargetPoint* LeavingPoint;

public:
	void CustomBeginPlay();
	bool TrySatisfy(class UNeedComponent* Need, class AAlien* Alien);
	void Satisfy();
	bool CheckAccessibility(FVector Start, FVector End);
	void Wait();
	void DoTask();
	void SatisfiedAlien();
	void Wander(class AAlien* Alien);
	void Leave(class AAlien* Alien);

};

