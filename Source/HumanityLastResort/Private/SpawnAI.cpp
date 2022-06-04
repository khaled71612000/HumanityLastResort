// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnAI.h"
#include "AI/Alien.h"
#include "AI/AlienSubsystem.h"
#include "TimerManager.h"
#include "AI/NeedComponent.h"
#include "Buildings/Resturant.h"

void ASpawnAI::BeginPlay() 
{
	AlienSubsystem = GetWorld()->GetSubsystem<UAlienSubsystem>();

	SpawnParams.Owner = this;
	SpawnLocation = this->GetActorLocation();
	SpawnRotation = this->GetActorRotation();

	FTimerHandle SpawningManager;
	GetWorld()->GetTimerManager().SetTimer(SpawningManager, this, &ASpawnAI::SpawnAnAlien, SpawnRate, true);
}

void ASpawnAI::SpawnAnAlien()
{
	int32 AlienInd = FMath::RandRange(0,  3);
	AAlien* Alien = GetWorld()->SpawnActor<AAlien>(Aliens[AlienInd], SpawnLocation, SpawnRotation, SpawnParams);
	Alien->CallSetAlienAttributes();
	Alien->CallSetAlienNeedsValues();
	AlienSubsystem->Aliens.Add(Alien);
	AlienSubsystem->NumOfAliens++;
	
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Spawn"));
}





