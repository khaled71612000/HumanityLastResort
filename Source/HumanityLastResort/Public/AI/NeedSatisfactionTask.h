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

public:
	virtual void Satisfy(class AAlien* Alien, class UNeedComponent* Need, TSubclassOf<class ABuilding> CurrentBuilding);
	void Wait();
	void DoTask();
	void ShuffleBuildings(TArray<AActor*> &Buildings);

	class ABuilding* GetBuilding();
	void MoveToBuilding(class ABuilding* Building);

protected:
	class AAlien* CurrentAlien;
	class UNeedComponent* TaskComponent;
	TSubclassOf<class ABuilding> CurrentBuildingType;
	float CurTaskTime;
	FTimerHandle TaskTimeManager;
};

