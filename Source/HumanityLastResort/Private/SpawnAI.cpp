// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnAI.h"
#include "EconomySubsystem.h"
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
	GetWorld()->GetTimerManager().SetTimer(SpawningManager, this, &ASpawnAI::SpawnAnAlien, SpawnRate, true);
}

void ASpawnAI::SpawnAnAlien()
{
	AAlien* Alien = GetWorld()->SpawnActor<AAlien>(ActorToSpawn,SpawnLocation, SpawnRotation, SpawnParams);
	AlienSubsystem->Aliens.Add(Alien);

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Spawn"));

}
