// Fill out your copyright notice in the Description page of Project Settings.


#include "AEGameModeBase.h"
// Sets default values
AAEGameModeBase::AAEGameModeBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
} 


// Called when the game starts or when spawned
void AAEGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void AAEGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
