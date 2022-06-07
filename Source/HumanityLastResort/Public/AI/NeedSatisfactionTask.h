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
	class AAlien* CurrentAlien;
	class UNeedComponent* TaskComponent;
	int32 CurBuildingType;
	float CurTaskTime;
	FTimerHandle TaskTimeManager;
	class ABuilding* GetBuilding();

public:
	virtual void Satisfy(class AAlien* Alien, class UNeedComponent* Need);
	void Wait();
	void DoTask();
	void ShuffleBuildings(TArray<class ABuilding*> &Buildings);
	void ResetAlien();
	void MoveToBuilding(class ABuilding* Building);


};

