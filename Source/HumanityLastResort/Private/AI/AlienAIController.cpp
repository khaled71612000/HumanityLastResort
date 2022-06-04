// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AlienAIController.h"
#include "AI/Alien.h"
#include "Building.h"
#include "Buildings/Casino.h"

void AAlienAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{		
	AAlien* Alien = Cast<AAlien>(GetPawn());

	if(RequestID.IsValid())
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Valid");
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "InValid");


	if (Result.IsSuccess())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Success");
		StopMovement();

		if (Alien)
		{
			if (Alien->AlienState == Leaving)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Leaving"));

				Alien->Destroy();
			}
			else if (Alien->AlienState == Assigned)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Assigned"));
				AlienFailedUpdate(Alien);
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("Not Assigned"));
				AlienSucceedUpdate(Alien);
			}
		}
	}

	else if (Result.IsFailure())
	{
		if (Alien) {
			Alien->AlienState = Idle;
			CurBuilding->CurOccupants--;
		}
			
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Failure");

	}

	else if(Result.IsInterrupted())
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Interrupted");
	else 
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "SomethingElse");

	
}

void AAlienAIController::AlienSucceedUpdate(AAlien* Alien)
{
	Alien->NumOfTasks--;
	if (Alien->NumOfTasks == 0)
		Alien->AlienState = Leaving;

	Alien->ChangeMood(Alien->GoodMoodVal);

	CurBuilding->AddProfit();
	if (Cast<ACasino>(CurBuilding))
	{
		Alien->isDancing = true;
	}
}

void AAlienAIController::AlienFailedUpdate(AAlien* Alien)
{
	Alien->NumOfFailedTasks--;
	if (Alien->NumOfFailedTasks == 0)
		Alien->AlienState = Leaving;
	else
		Alien->AlienState = Idle;

	Alien->ChangeMood(-Alien->BadMoodVal);

	//Building Update
	CurBuilding->CurOccupants--;
	CurBuilding->SubtractLoss();
}

