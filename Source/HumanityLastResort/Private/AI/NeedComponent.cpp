
#include "AI/NeedComponent.h"
#include "AI/NeedSubsystem.h"

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
	NeedSubsystem = GetWorld()->GetSubsystem<UNeedSubsystem>();
	CurValue = MaxCapacity;
	StartDecreasingValue();
}

void UNeedComponent::StartDecreasingValue()
{
	GetWorld()->GetTimerManager().SetTimer(TimerManager, this, &UNeedComponent::DecreaseValue, 1.f, true);
}

void UNeedComponent::DecreaseValue()
{
	if (CurValue > 0)
		CurValue -= DecayRate;
	if (CurValue == Threshold)
	{
		Needed = true;
		NeedSubsystem->IncrementNeed(BuildingType);
	}
}

void UNeedComponent::DecrementNeededVal()
{
	NeedSubsystem->DecrementNeed(BuildingType);

}
