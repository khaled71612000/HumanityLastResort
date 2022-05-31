// Fill out your copyright notice in the Description page of Project Settings.


#include "NewCell.h"

// Sets default values
ANewCell::ANewCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->AttachTo(RootComponent);
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ANewCell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANewCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

