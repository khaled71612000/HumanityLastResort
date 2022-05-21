// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AlienSubsystem.h"
#include "AI/Alien.h"


TStatId UAlienSubsystem::GetStatId() const
{
	return TStatId();
}

void UAlienSubsystem::Tick(float DeltaTime)
{
	for (AAlien* Alien : Aliens)
	{
		if (Alien->AlienState == Idle)
		{
			Alien->GetTask();
			Alien->GoToTask();
			UE_LOG(LogTemp, Warning, TEXT("Value: %d"));

		}
		else if (Alien->AlienState == Arrived)
			Alien->DoTask();
	}
}


