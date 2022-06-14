// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/NeedSatisfactionTask.h"
#include "AI/Alien.h"
#include "AI/AlienAIController.h"
#include "AI/NeedComponent.h"
#include "Building.h"
#include "Kismet/GameplayStatics.h"
#include "Buildings/BuildingSubsystem.h"
#include "NavigationData.h"
#include "NavigationSystem.h"


bool UNeedSatisfactionTask::TrySatisfy(UNeedComponent* Need, AAlien* Alien)
{
	UNavigationSystemV1* NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	if (!NavArea)
		return false;
	FPathFindingQuery QueryParams;
	QueryParams.StartLocation = Alien->GetActorLocation();
	QueryParams.Owner = this;
	QueryParams.NavData = NavArea->GetDefaultNavDataInstance();
	QueryParams.SetAllowPartialPaths(false);

	CurBuildingType = Need->BuildingType;

	for (ABuilding* Building : Need->BuildingSubsystem->Buildings[CurBuildingType])
	{
		QueryParams.EndLocation = Building->GetActorLocation();
		
		if (NavArea->TestPathSync(QueryParams, EPathFindingMode::Hierarchical))
		{
			CurAlien = Alien;
			CurNeed = Need;
			CurBuilding = Building;
			//UE_LOG(LogTemp, Warning, TEXT("True"));

			return true;
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("False"));
	return false;
}

void UNeedSatisfactionTask::Satisfy()
{
	AAlienAIController* AI = Cast<AAlienAIController>(CurAlien->GetController());
	if (AI)
	{
		CurBuilding->CurOccupants++;
		CurAlien->AlienState = Assigned;
		AI->CurBuilding = CurBuilding;
		AI->MoveToLocation(CurBuilding->GetActorLocation(), 25.f);
	}
	
}

void UNeedSatisfactionTask::Wait()
{
	CurTaskTime = CurNeed->TaskTime;
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
		ResetAlien();
	}
}


void UNeedSatisfactionTask::ResetAlien()
{
	if (CurAlien->isDancing == true)
		CurAlien->isDancing = false;

	CurNeed->CurValue = CurNeed->MaxCapacity;
	if(CurAlien->NumOfTasks == 0 || CurAlien->NumOfFailedTasks == 0)
		CurAlien->AlienState = Leaving;
	else
		CurAlien->AlienState = Idle;

	GetWorld()->GetTimerManager().PauseTimer(TaskTimeManager);
	CurTaskTime = CurNeed->TaskTime;
}
