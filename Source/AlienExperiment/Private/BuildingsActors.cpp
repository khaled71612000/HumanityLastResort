// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingsActors.h"

ABuildingsActors::ABuildingsActors()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMeshComponent;
	//StaticMeshComponent->SetRelativeScale3D(FVector(0.75f, 0.75f, 1.5f));
}

void ABuildingsActors::LockPosition(bool block)
{
	if (StaticMeshComponent->GetBodyInstance()->bLockXTranslation) {
		StaticMeshComponent->GetBodyInstance()->bLockXTranslation = false;
		StaticMeshComponent->GetBodyInstance()->bLockYTranslation = false;
		StaticMeshComponent->GetBodyInstance()->bLockZTranslation = false;
		StaticMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
		StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	}
	else {
		StaticMeshComponent->GetBodyInstance()->bLockXTranslation = true;
		StaticMeshComponent->GetBodyInstance()->bLockYTranslation = true;
		StaticMeshComponent->GetBodyInstance()->bLockZTranslation = true;
		StaticMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
		StaticMeshComponent->SetMobility(EComponentMobility::Static);
	}
}

void ABuildingsActors::BeginPlay()
{
	Super::BeginPlay();
	
}

