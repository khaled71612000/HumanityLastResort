// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NeedSatisfactionTask.h"
#include "AI/Alien.h"

void UNeedSatisfactionTask::Satisfy(AAlien* Alien, class UNeedComponent* Need)
{
	UE_LOG(LogTemp, Warning, TEXT("Parent"));
}

void UNeedSatisfactionTask::Wait()
{
}
