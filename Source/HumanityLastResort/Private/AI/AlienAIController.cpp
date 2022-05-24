// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AlienAIController.h"
#include "AI/Alien.h"
#include "BuildingsActors.h"

void AAlienAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	AAlien* Alien = Cast<AAlien>(GetPawn());
	if (Alien)
	{
		if (Alien->AlienState == Leaving)
		{
			Alien->Destroy();
		}
		else if (Alien->AlienState == Assigned)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Assigned"));

			//Alien Update
			Alien->NumOfFailedTasks--;
			if (Alien->NumOfFailedTasks == 0)
				Alien->AlienState = Leaving;
			else
				Alien->AlienState = Idle;

			CurBuilding->CurOccupants--;
			Alien->ChangeMood(-Alien->BadMoodVal);

			//Building Update
			CurBuilding->SubtractLoss();
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Not Assigned"));
			Alien->NumOfTasks--;
			if (Alien->NumOfTasks == 0)
				Alien->AlienState = Leaving;

			Alien->ChangeMood(Alien->GoodMoodVal);
			CurBuilding->AddProfit();
		}
	}
}