// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/NeedSatisfactionTask.h"
#include "AI/Alien.h"
#include "AI/AlienAIController.h"
#include "AI/NeedComponent.h"
#include "Building.h"
#include "Road.h"
#include "Kismet/GameplayStatics.h"
#include "Buildings/BuildingSubsystem.h"
#include "RoadSubsystem.h"
#include "NavigationData.h"
#include "NavigationSystem.h"


bool UNeedSatisfactionTask::TrySatisfy(UNeedComponent* Need, AAlien* Alien)
{
	CurBuildingType = Need->BuildingType;
	UBuildingSubsystem* BuildingSubsystem = GetWorld()->GetSubsystem<UBuildingSubsystem>();

	for (ABuilding* Building : BuildingSubsystem->Buildings[CurBuildingType])
	{
		
		if (CheckAccessibility(Alien->GetActorLocation(), Building->GetActorLocation()))
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

bool UNeedSatisfactionTask::CheckAccessibility(FVector Start, FVector End)
{
	UNavigationSystemV1* NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	if (!NavArea)
		return false;
	FPathFindingQuery QueryParams;
	QueryParams.StartLocation = Start;
	QueryParams.EndLocation = End;
	QueryParams.Owner = this;
	QueryParams.NavData = NavArea->GetDefaultNavDataInstance();
	QueryParams.SetAllowPartialPaths(false);

	return NavArea->TestPathSync(QueryParams, EPathFindingMode::Hierarchical);
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

void UNeedSatisfactionTask::Wander(AAlien* Alien)
{
	URoadSubsystem* RoadSubsystem = GetWorld()->GetSubsystem<URoadSubsystem>();
	int32 NumOfRoads = RoadSubsystem->Roads.Num();
	if (NumOfRoads > 1)
	{
		int32 RandRoad = FMath::RandRange(0, NumOfRoads - 1);
		if (CheckAccessibility(Alien->GetActorLocation(), RoadSubsystem->Roads[RandRoad]->GetActorLocation()))
		{
			AAlienAIController* AI = Cast<AAlienAIController>(Alien->GetController());
			if (AI)
			{
				AI->MoveToLocation(RoadSubsystem->Roads[RandRoad]->GetActorLocation());
			}
		}

		else
		{
			Alien->AlienState = Idle;
		}
	}
	else
		Alien->AlienState = Idle;

}
