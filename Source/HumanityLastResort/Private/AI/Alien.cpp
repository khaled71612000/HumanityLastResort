// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Alien.h"
#include "AI/NeedComponent.h"
#include "AI/NeedSatisfactionTask.h"
#include "AI/AlienSubsystem.h"
#include "AI/AlienAIController.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"


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
	AlienSubsystem = GetWorld()->GetSubsystem<UAlienSubsystem>();
}

void AAlien::GetTask()
{
	TArray<UNeedComponent*> Needs;
	GetComponents(Needs);

	int MinValue = 101;
	for (UNeedComponent* Need : Needs)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Task: %d"), Need->CurValue);

		if (Need->CurValue < MinValue)
		{
			NeedToExcute = Need;
			MinValue = Need->CurValue;
		}
	}
}

void AAlien::GoToTask()
{
	if (NeedToExcute)
		NeedToExcute->Task->Satisfy(this, NeedToExcute, NeedToExcute->Building);
	else
		AlienState = Idle;
}

void AAlien::DoTask()
{
	if (NeedToExcute)
		NeedToExcute->Task->Wait();

}

void AAlien::Leave()
{
	AAlienAIController* AI = Cast<AAlienAIController>(GetController());
	AI->MoveToLocation(UGameplayStatics::GetActorOfClass(GetWorld(), ATargetPoint::StaticClass())->GetActorLocation(), 5.f);
}

void AAlien::ChangeMood(int MoodVal)
{
	AlienSubsystem->GlobalMood -= Mood;
	Mood += MoodVal;
	AlienSubsystem->GlobalMood += Mood;
	AlienSubsystem->UpdateGlobalMood();

	//UE_LOG(LogTemp, Warning, TEXT("Mood: %d"), AlienSubsystem->GlobalMood);

}


