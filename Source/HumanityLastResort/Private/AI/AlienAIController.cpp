// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AlienAIController.h"
#include "AI/Alien.h"
#include "BuildingsActors.h"

void AAlienAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	AAlien* Alien = Cast<AAlien>(GetPawn());
	if (Alien)
	{
		if (Alien->AlienState == Assigned)
		{
			UE_LOG(LogTemp, Warning, TEXT("AI here"));

			Alien->AlienState = Idle;
			CurBuilding->CurOccupants--;
		}
	}
}