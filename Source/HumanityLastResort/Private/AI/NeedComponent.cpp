// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NeedComponent.h"
#include "AI/NeedSatisfactionTask.h"
#include "AI/HungerSatisfactionTask.h"


// Sets default values for this component's properties
UNeedComponent::UNeedComponent()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void UNeedComponent::OnRegister()
{
	Super::OnRegister();
	if (TaskClass) 
	{
		Task = NewObject<UNeedSatisfactionTask>(this, TaskClass);
	}	

}

// Called when the game starts
void UNeedComponent::BeginPlay()
{
	Super::BeginPlay();
	CurValue = MaxCapacity;
	StartDecreasingValue();
}



void UNeedComponent::StartDecreasingValue()
{
	FTimerHandle TimerManager;
	GetWorld()->GetTimerManager().SetTimer(TimerManager, this, &UNeedComponent::DecreaseValue, 1.f, true);

}

void UNeedComponent::DecreaseValue()
{
	if (CurValue > 0)
		CurValue -= DecayRate;
	UE_LOG(LogTemp, Warning, TEXT("CurValue: %f"), CurValue);
	UE_LOG(LogTemp, Warning, TEXT("MaxCapacity: %d"), MaxCapacity);
}
