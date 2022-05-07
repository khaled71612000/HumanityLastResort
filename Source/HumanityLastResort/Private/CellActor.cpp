// Fill out your copyright notice in the Description page of Project Settings.


#include "CellActor.h"

ACellActor::ACellActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    StaticMeshComponent->SetupAttachment(RootComponent);
	//StaticMeshComponent->SetRelativeScale3D(FVector(0, 0, 0.25f));
	SetReplicates(true);
}

void ACellActor::BeginPlay()
{
	Super::BeginPlay();
	
}



