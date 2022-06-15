
#include "AI/NeedComponent.h"
#include "AI/NeedSatisfactionTask.h"
#include "Buildings/BuildingSubsystem.h"
#include "AI/Alien.h"

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

	if (CurValue < Threshold)
	{
		AAlien* Owner = (AAlien*)GetOwner();
		if(Owner->AlienState == Wandering)
			Owner->AlienState = Idle;
	}

}
