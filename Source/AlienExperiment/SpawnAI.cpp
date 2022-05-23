// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnAI.h"
#include "AICharacterBase.h"
#include "TimerManager.h"

void ASpawnAI::BeginPlay() 
{
	SpawnParams.Owner = this;
	SpawnLocation = this->GetActorLocation();
	SpawnRotation = this->GetActorRotation();

	FTimerHandle SpawningManager;
	GetWorld()->GetTimerManager().SetTimer(SpawningManager, this, &ASpawnAI::SpawnAnAlien, SpawnRate, false);

}

void ASpawnAI::SpawnAnAlien()
{
	GetWorld()->SpawnActor<AAICharacterBase>(ActorToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
}
