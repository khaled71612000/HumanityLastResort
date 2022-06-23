// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NeedSubsystem.h"
#include "AI/NeedComponent.h"

void UNeedSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	NeedsStats.Init(0, NumOfNeeds);

}

void UNeedSubsystem::IncrementNeed(int32 NeedIndex)
{
	NeedsStats[NeedIndex]++;
}

void UNeedSubsystem::DecrementNeed(int32 NeedIndex)
{
	NeedsStats[NeedIndex]--;
}

