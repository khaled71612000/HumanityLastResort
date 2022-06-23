// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AlienAIController.h"
#include "AI/Alien.h"
#include "Building.h"
#include "Buildings/Casino.h"

void AAlienAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{		
	StopMovement();
	AAlien* Alien = Cast<AAlien>(GetPawn());

	if (Alien->AlienState == Moving)
	{
		Alien->SetActorHiddenInGame(true);
		Alien->SetActorEnableCollision(false);
		Alien->RemoveAlien();
	}
	else if(Alien->AlienState == Wandering)
	{
		if (Alien->CurFailedTasks <= 0 || Alien->CurTasks <=0)
			Alien->AlienState = Leaving;
		else
			Alien->AlienState = Idle;

	}
	else if (Result.IsSuccess())
	{
		if (Alien->AlienState == Assigned)
		{
			Alien->AlienState = Arrived;
			AlienSucceedUpdate(Alien);
		}
	}
	else if (Result.IsFailure())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed: %d"), Alien->AlienState);

		if (Alien->AlienState == Assigned)
		{
			Alien->AlienState = Idle;
			AlienFailedUpdate(Alien);
			CurBuilding->CurOccupants--;
		}	
	}
}

void AAlienAIController::AlienSucceedUpdate(AAlien* Alien)
{
	Alien->CurTasks--;
	Alien->ChangeMood(Alien->GoodMoodVal);

	CurBuilding->AddProfit();
	if (CurBuilding->BuildingType == Casino)
	{
		Alien->isDancing = true;
	}
}

void AAlienAIController::AlienFailedUpdate(AAlien* Alien)
{
	Alien->CurFailedTasks--;
	if (Alien->CurFailedTasks <= 0)
		Alien->AlienState = Leaving;

	Alien->ChangeMood(-Alien->BadMoodVal);

	//Building Update
	CurBuilding->CurOccupants--;
	CurBuilding->SubtractLoss();
}