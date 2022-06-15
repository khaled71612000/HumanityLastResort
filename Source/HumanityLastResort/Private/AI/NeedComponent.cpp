
#include "AI/NeedComponent.h"
#include "AI/NeedSatisfactionTask.h"
#include "Buildings/BuildingSubsystem.h"

UNeedComponent::UNeedComponent()
{
	PrimaryComponentTick.bCanEverTick = false;	
	MaxCapacity = 100;
	Threshold = 50;
}

void UNeedComponent::OnRegister()
{
	Super::OnRegister();
}

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
}
