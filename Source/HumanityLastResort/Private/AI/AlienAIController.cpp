// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AlienAIController.h"
#include "AI/Alien.h"

void AAlienAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	AAlien* Alien = Cast<AAlien>(GetPawn());
	if (Alien)
	{
		if(Alien->AlienState == Assigned)
			Alien->AlienState = Idle;
		//UE_LOG(LogTemp, Warning, TEXT("OnMoveCompleted"));
	}
}