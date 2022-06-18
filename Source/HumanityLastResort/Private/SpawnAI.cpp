// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnAI.h"
#include "AI/Alien.h"
#include "AI/AlienSubsystem.h"
#include "TimerManager.h"


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
	int32 AlienInd = FMath::RandRange(0,  Aliens.Num()-1);
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
		AliensToSpawn[AlienInd].AlienType[SpawnAlienTypeInd[AlienInd]]->FinishSpawning({ SpawnRotation, SpawnLocation, SpawnScale });
		AlienToSpawn = AliensToSpawn[AlienInd].AlienType[SpawnAlienTypeInd[AlienInd]];
		SpawnAlienTypeInd[AlienInd]++;
	}
	AlienSubsystem->SpawnedAliens.Add(AlienToSpawn);
	AlienSubsystem->NumOfAliens++;
	AlienSubsystem->GlobalMood += 100;
	
}
