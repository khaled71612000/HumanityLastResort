#include "AI/NeedComponent.h"
#include "AI/NeedSatisfactionTask.h"
#include "Buildings/BuildingSubsystem.h"

UNeedComponent::UNeedComponent()
{
	PrimaryComponentTick.bCanEverTick = false;	
	MaxCapacity = 100;
}

void UNeedComponent::OnRegister()
{
	Super::OnRegister();

}

void UNeedComponent::BeginPlay()
{
	Super::BeginPlay();
	BuildingSubsystem = GetWorld()->GetSubsystem<UBuildingSubsystem>();
	Task = NewObject<UNeedSatisfactionTask>(this);
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
	//UE_LOG(LogTemp, Warning, TEXT("CurValue: %f"), CurValue);
	//UE_LOG(LogTemp, Warning, TEXT("DecayRate: %f"), DecayRate);
}
