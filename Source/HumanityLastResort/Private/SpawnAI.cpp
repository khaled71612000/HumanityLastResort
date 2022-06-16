// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnAI.h"
#include "AI/Alien.h"
#include "AI/AlienSubsystem.h"
#include "TimerManager.h"


void ASpawnAI::BeginPlay() 
{
	AlienSubsystem = GetWorld()->GetSubsystem<UAlienSubsystem>();

	SpawnParams.Owner = this;
	SpawnLocation = this->GetActorLocation();
	SpawnRotation = this->GetActorRotation();

	FTimerHandle SpawningManager;
	GetWorld()->GetTimerManager().SetTimer(SpawningManager, this,
		&ASpawnAI::SpawnAnAlien, 10, true);

}

void ASpawnAI::SpawnAnAlien()
{
	int32 AlienInd = FMath::RandRange(0,  Aliens.Num()-1);
	AAlien* AlienToSpawn;
	if (AlienSubsystem->AliensPool[AlienInd].Aliens.Num() > 0)
	{
		AlienToSpawn = AlienSubsystem->AliensPool[AlienInd].Aliens.Last();
		AlienToSpawn->SetActorEnableCollision(true);
		AlienToSpawn->SetActorHiddenInGame(false);
		AlienToSpawn->SetActorLocation(SpawnLocation);
		AlienSubsystem->AliensPool[AlienInd].Aliens.Pop();
	}
	else
	{
		AlienToSpawn = GetWorld()->SpawnActor<AAlien>(Aliens[AlienInd], SpawnLocation, SpawnRotation, SpawnParams);
	}
	AlienSubsystem->SpawnedAliens.Add(AlienToSpawn);
	AlienSubsystem->NumOfAliens++;
	AlienSubsystem->GlobalMood += 100;
	
}





