// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NeedSatisfactionTask.h"
#include "AI/Alien.h"
#include "AI/AlienAIController.h"
#include "AI/NeedComponent.h"
#include "Building.h"
#include "Buildings/Resturant.h"
#include "Kismet/GameplayStatics.h"


void UNeedSatisfactionTask::Satisfy(AAlien* Alien, class UNeedComponent* Need, TSubclassOf<class ABuilding> BuildingType)
{
	CurrentBuildingType = BuildingType;
	CurrentAlien = Alien;
	TaskComponent = Need;

	ABuilding* Building = GetBuilding();
	if(Building)
		MoveToBuilding(Building);
	else
		Alien->AlienState = Idle;
}

void UNeedSatisfactionTask::Wait()
{
	CurTaskTime = TaskComponent->TaskTime;
	if (GetWorld()->GetTimerManager().IsTimerPaused(TaskTimeManager))
		GetWorld()->GetTimerManager().UnPauseTimer(TaskTimeManager);
	else
		GetWorld()->GetTimerManager().SetTimer(TaskTimeManager, this, &UNeedSatisfactionTask::DoTask, 1.f, true);
}

void UNeedSatisfactionTask::DoTask()
{
	CurTaskTime--;

	if (CurTaskTime <= 0)
	{
		TaskComponent->CurValue = TaskComponent->MaxCapacity;
		CurrentAlien->AlienState = Idle;
		GetWorld()->GetTimerManager().PauseTimer(TaskTimeManager);
		CurTaskTime = TaskComponent->TaskTime;
	}
}

void UNeedSatisfactionTask::ShuffleBuildings(TArray<AActor*>& Buildings)
{
	int32 NumOfBuildings = Buildings.Num();
	int32 ShuffleTurns = NumOfBuildings / 2;
	int32 Index1;
	int32 Index2;
	AActor* Temp;

	if (NumOfBuildings > 1)
	{
		while (ShuffleTurns--)
		{
			Index1 = FMath::RandRange(0, NumOfBuildings - 1);
			Index2 = FMath::RandRange(0, NumOfBuildings - 1);
			Temp = Buildings[Index1];
			Buildings[Index1] = Buildings[Index2];
			Buildings[Index2] = Temp;
		}
	}
}

ABuilding* UNeedSatisfactionTask::GetBuilding()
{
	TArray<AActor*> Buildings;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CurrentBuildingType, Buildings);

	ShuffleBuildings(Buildings);

	for (AActor* Building : Buildings)
	{
		ABuilding* B = Cast<ABuilding>(Building);
		if (B)
		{
			if (B->CurOccupants < B->Capacity)
				return B;
		}
	}
	return nullptr;
}

void UNeedSatisfactionTask::MoveToBuilding(ABuilding* Building)
{
	if (Building)
	{
		AAlienAIController* AI = Cast<AAlienAIController>(CurrentAlien->GetController());
		if (AI)
		{
			Building->CurOccupants++;
			//UE_LOG(LogTemp, Warning, TEXT("Rest: %d"), Hotel->CurOccupants);
			CurrentAlien->AlienState = Assigned;
			AI->CurBuilding = Building;
			AI->MoveToLocation(Building->GetActorLocation());
		}
	}
}


