// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnAI.h"
#include "AI/Alien.h"
#include "AI/AlienSubsystem.h"
#include "TimerManager.h"
#include "AI/NeedSatisfactionTask.h"
#include "AI/NeedComponent.h"


void ASpawnAI::BeginPlay()
{
	AliensToSpawn.SetNum(NumOfAliensType);
	SpawnAlienTypeInd.Init(0, NumOfAliensType);

	SpawnParams.Owner = this;
	SpawnLocation = this->GetActorLocation();
	SpawnRotation = this->GetActorRotation();
	SpawnScale = { 1, 1, 1 };

	SpawnAllAliens();

	AlienSubsystem = GetWorld()->GetSubsystem<UAlienSubsystem>();
	AlienSubsystem->SpawnRateUpdate.AddDynamic(this, &ASpawnAI::UpdateSpawnTimer);

	UpdateSpawnTimer(InitialSpawnRate);
}


void ASpawnAI::SpawnAllAliens()
{
	for (int32 i = 0; i < NumOfAliensType; i++)
	{
		for (int32 j = 0; j < NumOfAllAliensToSpawn; j++)
		{
			AliensToSpawn[i].AlienType.Add(GetWorld()->SpawnActorDeferred<AAlien>(Aliens[i], { SpawnRotation, SpawnLocation, SpawnScale }));
			AliensToSpawn[i].AlienType[j]->SetActorEnableCollision(false);
			AliensToSpawn[i].AlienType[j]->SetActorHiddenInGame(true);
		}
	}
}


void ASpawnAI::UpdateSpawnTimer(int32 SpawnRate)
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnManager);
	GetWorld()->GetTimerManager().SetTimer(SpawnManager, this,
		&ASpawnAI::SpawnAnAlien, SpawnRate, true);
}


void ASpawnAI::SpawnAnAlien()
{
	int32 AlienInd = FMath::RandRange(0, Aliens.Num() - 1);
	if (AlienSubsystem->AliensPool[AlienInd].Aliens.Num() > 0)
	{
		AlienToSpawn = AlienSubsystem->AliensPool[AlienInd].Aliens.Last();
		AlienSubsystem->AliensPool[AlienInd].Aliens.Pop();
	}
	else
	{

		AlienToSpawn = AliensToSpawn[AlienInd].AlienType[SpawnAlienTypeInd[AlienInd]];
		AlienToSpawn->FinishSpawning({ SpawnRotation, SpawnLocation, SpawnScale });
		SpawnAlienTypeInd[AlienInd]++;
		InitAlienComponents(AlienToSpawn);

	}
	InitAlien(AlienToSpawn);
	AlienSubsystem->SpawnedAliens.Add(AlienToSpawn);
	AlienSubsystem->NumOfAliens++;

	OnSpawning();

}

void ASpawnAI::InitAlien(AAlien* Alien)
{
	Alien->SetActorLocation(SpawnLocation);
	Alien->SetActorEnableCollision(true);
	Alien->SetActorHiddenInGame(false);
	Alien->CurTasks = Alien->NumOfTasks;
	Alien->CurFailedTasks = Alien->NumOfFailedTasks;
	Alien->AlienState = Idle;
	Alien->isDancing = false;
	Alien->Mood = 0;

	for (int32 i = 0; i < Alien->Needs.Num(); i++)
	{
		Alien->Needs[i]->StartDecreasingValue();
	}
}

void ASpawnAI::InitAlienComponents(AAlien* Alien)
{
	AlienToSpawn->GetComponents(AlienToSpawn->Needs);
	Alien->Task = NewObject<UNeedSatisfactionTask>(this);
	Alien->Task->CustomBeginPlay();
	AlienSubsystem = GetWorld()->GetSubsystem<UAlienSubsystem>();
}
