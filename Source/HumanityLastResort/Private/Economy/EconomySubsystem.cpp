// Fill out your copyright notice in the Description page of Project Settings.


#include "Economy/EconomySubsystem.h"


void UEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Cash = 0;
}

void UEconomySubsystem::AddCash(int32 Amount)
{
	Cash += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Add: %d"), Cash);

}

void UEconomySubsystem::SubtractCash(int32 Amount)
{
	Cash -= Amount;
	UE_LOG(LogTemp, Warning, TEXT("Sub: %d"), Cash);

}