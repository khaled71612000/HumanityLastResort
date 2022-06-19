

#include "Economy/EconomySubsystem.h"

void UEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Cash = 200000;
}

void UEconomySubsystem::AddCash(int32 Amount)
{
	Cash += Amount;
}

void UEconomySubsystem::SubtractCash(int32 Amount)
{
	Cash -= Amount;
}

int32 UEconomySubsystem::GetCash()
{
	return Cash;
}
