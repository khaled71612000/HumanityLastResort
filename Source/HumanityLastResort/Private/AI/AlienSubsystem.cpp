// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AlienSubsystem.h"
#include "AI/Alien.h"


void UAlienSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GlobalMood = 0;
	NumOfAliens = 0;
	GlobalMoodPercentage = 1.f;
}

TStatId UAlienSubsystem::GetStatId() const
{
	return TStatId();
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
		else if (Alien->AlienState == Leaving)
		{
			UpdateNumOfAliens(Alien);
			UpdateGlobalMood();
			Alien->Leave();
			break;
		}
	}
}

void UAlienSubsystem::UpdateNumOfAliens(class AAlien* Alien)
{
	NumOfAliens--;
	GlobalMood -= Alien->Mood;
	Aliens.Remove(Alien);
}

void UAlienSubsystem::UpdateGlobalMood()
{
	if (NumOfAliens)
		GlobalMoodPercentage = GlobalMood / (float)NumOfAliens;

	/*UE_LOG(LogTemp, Warning, TEXT("Global Mood: %d"), GlobalMood);
	UE_LOG(LogTemp, Warning, TEXT("Global Mood Percentage: %f"), GlobalMoodPercentage);
	UE_LOG(LogTemp, Warning, TEXT("Num of Aliens: %d"), NumOfAliens);*/

}

float UAlienSubsystem::GetGlobalMoodPercentage()
{
	return GlobalMoodPercentage;
}

int32 UAlienSubsystem::GetNumOfAliens()
{
	return NumOfAliens;
}


