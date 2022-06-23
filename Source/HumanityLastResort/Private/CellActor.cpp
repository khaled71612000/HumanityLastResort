// Fill out your copyright notice in the Description page of Project Settings.


#include "CellActor.h"
#include "GameFramework/PlayerController.h"


ACellActor::ACellActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    StaticMeshComponent->SetupAttachment(RootComponent);
	SetReplicates(true);
}

void ACellActor::BeginPlay()
{
	Super::BeginPlay();

	FHitResult Hit;


}



