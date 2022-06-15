// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AlienSubsystem.h"
#include "AI/Alien.h"

void UAlienSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	AliensPool.SetNum(NumOfAlienTypes);
	GlobalMood = 0;
	NumOfAliens = 0;
	GlobalMoodPercentage = 100;
}

TStatId UAlienSubsystem::GetStatId() const
{
	return TStatId();
}

void UAlienSubsystem::Tick(float DeltaTime)
{
	for (AAlien* Alien : SpawnedAliens)
	{
		UE_LOG(LogTemp, Warning, TEXT("Alien: %d"), Alien->AlienState);

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
			SubtractAlienInfo(Alien);
			Alien->Leave();
			break;
		}
	}
}

void UAlienSubsystem::SubtractAlienInfo(class AAlien* Alien)
{
	NumOfAliens--;
	UpdateGlobalMood(-Alien->Mood);
	SpawnedAliens.Remove(Alien);
}

void UAlienSubsystem::UpdateGlobalMood(int32 Amount)
{
	GlobalMood += Amount;
	if (GlobalMood < 0)
		GlobalMood = 0;

	UpdateGlobalMoodPercentage();
}

void UAlienSubsystem::UpdateGlobalMoodPercentage()
{
	if (NumOfAliens)
		GlobalMoodPercentage = (GlobalMood / (float)(NumOfAliens * 100)) * 100;

}

int32 UAlienSubsystem::GetGlobalMoodPercentage()
{
	return GlobalMoodPercentage;
}

int32 UAlienSubsystem::GetNumOfAliens()
{
	return NumOfAliens;
}