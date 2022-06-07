// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnAI.h"
#include "AI/Alien.h"
#include "AI/AlienSubsystem.h"
#include "TimerManager.h"
#include "Buildings/Resturant.h"

void ASpawnAI::BeginPlay() 
{
	AlienSubsystem = GetWorld()->GetSubsystem<UAlienSubsystem>();

	SpawnParams.Owner = this;
	SpawnLocation = this->GetActorLocation();
	SpawnRotation = this->GetActorRotation();

	FTimerHandle SpawningManager;
	GetWorld()->GetTimerManager().SetTimer(SpawningManager, this,
		&ASpawnAI::SpawnAnAlien, SpawnRate, true);
}

void ASpawnAI::SpawnAnAlien()
{
	int32 AlienInd = FMath::RandRange(0,  Aliens.Num()-1);
	AAlien* AlienToSpawn;
	if (AlienSubsystem->AliensPool[AlienInd].Num() > 0)
	{
		AlienToSpawn = AlienSubsystem->AliensPool[AlienInd].Last();
		AlienToSpawn->SetActorEnableCollision(true);
		AlienToSpawn->SetActorHiddenInGame(false);
		AlienToSpawn->SetActorLocation(SpawnLocation);
		AlienToSpawn->AlienState = Idle;
		AlienSubsystem->AliensPool[AlienInd].Pop();
	}
	else
	{
		AlienToSpawn = GetWorld()->SpawnActor<AAlien>(Aliens[AlienInd], SpawnLocation, SpawnRotation, SpawnParams);
	}
	AlienToSpawn->CallSetAlienAttributes();
	AlienToSpawn->CallSetAlienNeedsValues();
	AlienSubsystem->SpawnedAliens.Add(AlienToSpawn);
	AlienSubsystem->NumOfAliens++;
	
}





