// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AlienSubsystem.h"
#include "AI/Alien.h"
#include "SpawnAI.h"

void UAlienSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	AliensPool.SetNum(NumOfAlienTypes);
	GlobalMood = 75;
	NumOfAliens = 0;
}

TStatId UAlienSubsystem::GetStatId() const
{
	return TStatId();
}

void UAlienSubsystem::Tick(float DeltaTime)
{
	for (AAlien* Alien : SpawnedAliens)
	{
		if (!Alien)
			continue;
		if (Alien->AlienState == Idle)
		{
			Alien->AlienState = Waiting;
			Alien->TryGetTask();
		}
		else if (Alien->AlienState == Arrived)
		{
			Alien->AlienState = Waiting;
			Alien->DoTask();
		}
		else if (Alien->AlienState == Leaving)
		{
			Alien->AlienState = Moving;
			Alien->Leave();
			break;
		}
	}
}

void UAlienSubsystem::MoveAlienToPool(class AAlien* Alien)
{
	NumOfAliens--;
	SpawnedAliens.Remove(Alien);
	AliensPool[Alien->AlienType].Aliens.Add(Alien);
}


void UAlienSubsystem::UpdateGlobalMood(int32 Amount)
{
	GlobalMood += Amount;
	if (GlobalMood < 0) GlobalMood = 0;
	else if (GlobalMood > 100) GlobalMood = 100;

	if (GlobalMood > 80)
		SpawnRateUpdate.Broadcast(3);
	else if (GlobalMood > 60)
		SpawnRateUpdate.Broadcast(5);
	else if (GlobalMood > 40)
		SpawnRateUpdate.Broadcast(8);
	else if(GlobalMood < 30)
		GameOver.Broadcast();
}


int32 UAlienSubsystem::GetGlobalMood()
{
	return GlobalMood;
}

int32 UAlienSubsystem::GetNumOfAliens()
{
	return NumOfAliens;
}


