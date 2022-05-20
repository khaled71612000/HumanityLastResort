// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AlienSubsystem.h"
#include "AI/Alien.h"


TStatId UAlienSubsystem::GetStatId() const
{
	return TStatId();
}

void UAlienSubsystem::Tick(float DeltaTime)
{
	for (AAlien* Alien : Aliens)
	{
		/*Alien->GetTask();
		Alien->ExecuteTask();*/
	}

}


