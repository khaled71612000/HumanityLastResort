// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/NeedSatisfactionTask.h"
#include "AI/Alien.h"
#include "AI/AlienAIController.h"
#include "AI/NeedComponent.h"
#include "AI/NeedSubsystem.h"
#include "Building.h"
#include "Road.h"
#include "Kismet/GameplayStatics.h"
#include "Buildings/BuildingSubsystem.h"
#include "RoadSubsystem.h"
#include "NavigationData.h"
#include "NavigationSystem.h"
#include "Engine/TargetPoint.h"

void UNeedSatisfactionTask::CustomBeginPlay()
{
	BuildingSubsystem = GetWorld()->GetSubsystem<UBuildingSubsystem>();
	RoadSubsystem = GetWorld()->GetSubsystem<URoadSubsystem>();
	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	LeavingPoint = (ATargetPoint*)UGameplayStatics::GetActorOfClass(GetWorld(), ATargetPoint::StaticClass());
}


bool UNeedSatisfactionTask::TrySatisfy(UNeedComponent* Need, AAlien* Alien)
{
	CurBuildingType = Need->BuildingType;

	for (ABuilding* Building : BuildingSubsystem->Buildings[CurBuildingType].buildings)
	{
		
		if (Building->CurOccupants < Building->Capacity && CheckAccessibility(Alien->GetActorLocation(), Building->GetActorLocation()))
		{
			CurAlien = Alien;
			CurNeed = Need;
			CurBuilding = Building;
			return true;
		}
		else
		{
			Building->SubtractLoss();
		}
	}
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
		AI->MoveToLocation(CurBuilding->GetActorLocation(), 150.f);
	}
	
}


bool UNeedSatisfactionTask::CheckAccessibility(FVector Start, FVector End)
{
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
	if (CurBuilding->BuildingType != Casino) {
		CurAlien->SetActorHiddenInGame(true);
		CurAlien->SetActorEnableCollision(false);
	}
	const UWorld* const world = GetWorld();

	if (ensure(world != nullptr))
	{
		world->GetTimerManager().SetTimer(TaskTimeManager, this, &UNeedSatisfactionTask::DoTask, 1.f, true);
	}
}


void UNeedSatisfactionTask::DoTask()
{
	CurTaskTime--;

	if (CurTaskTime <= 0)
	{
		SatisfiedAlien();
		GetWorld()->GetTimerManager().ClearTimer(TaskTimeManager);
	}
}


void UNeedSatisfactionTask::SatisfiedAlien()
{
	if (CurBuilding->BuildingType != Casino) {
		CurAlien->SetActorHiddenInGame(false);
		CurAlien->SetActorEnableCollision(true);
	}
	if (CurAlien->isDancing == true)
		CurAlien->isDancing = false;

	CurNeed->CurValue = CurNeed->MaxCapacity;
	CurNeed->Needed = false;
	if(CurAlien->CurTasks == 0 || CurAlien->CurFailedTasks == 0)
		CurAlien->AlienState = Leaving;
	else
		CurAlien->AlienState = Idle;

	CurTaskTime = CurNeed->TaskTime;
	CurBuilding->CurOccupants--;
	CurNeed->NeedSubsystem->DecrementNeed(CurBuildingType);
}


void UNeedSatisfactionTask::Wander(AAlien* Alien)
{
	int32 NumOfRoads = RoadSubsystem->Roads.Num();

	if (NumOfRoads > 0)
	{
		int32 RandRoad = FMath::RandRange(0, NumOfRoads - 1);

		if (CheckAccessibility(Alien->GetActorLocation(), RoadSubsystem->Roads[RandRoad]->GetActorLocation()))
		{
			AAlienAIController* AI = Cast<AAlienAIController>(Alien->GetController());
			if (AI)
			{
				AI->MoveToLocation(RoadSubsystem->Roads[RandRoad]->GetActorLocation());
				return;
			}
		}
	}
	Alien->AlienState = Idle;

}


void UNeedSatisfactionTask::Leave(AAlien* Alien)
{
	AAlienAIController* AI = Cast<AAlienAIController>(Alien->GetController());
	if (AI)
	{
		AI->MoveToLocation(LeavingPoint->GetActorLocation(), 50.f);
	}

}
