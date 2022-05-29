// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AlienSubsystem.h"
#include "AI/Alien.h"


TStatId UAlienSubsystem::GetStatId() const
{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UAlienSubsystem, STATGROUP_Tickables);
}

void UAlienSubsystem::Tick(float DeltaTime)
{
	for (AAlien* Alien : Aliens)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Value: %d"), Alien->AlienState);
		if (Alien->AlienState == Idle)
		{
			Alien->AlienState = Waiting;
			Alien->GetTask();
			Alien->GoToTask();

		}
		else if (Alien->AlienState == Arrived)
		{
			Alien->AlienState = Waiting;
			Alien->DoTask();
		}
	}
}


