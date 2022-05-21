// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Alien.h"
#include "AI/NeedComponent.h"
#include "AI/NeedSatisfactionTask.h"

// Sets default values
AAlien::AAlien()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AlienState = Idle;
}

// Called when the game starts or when spawned
void AAlien::BeginPlay()
{
	Super::BeginPlay();
}

void AAlien::GetTask()
{
	TArray<UNeedComponent*> Needs;
	GetComponents(Needs);

	int MinValue = 101;
	for (UNeedComponent* Need : Needs)
	{
		if (Need->CurValue < MinValue)
		{
			NeedToExcute = Need;
			MinValue = Need->CurValue;
		}
	}
}

void AAlien::GoToTask()
{
	if(NeedToExcute)
		NeedToExcute->Task->Satisfy(this, NeedToExcute);
}

void AAlien::DoTask()
{
	if (NeedToExcute)
		NeedToExcute->Task->Wait();
}


