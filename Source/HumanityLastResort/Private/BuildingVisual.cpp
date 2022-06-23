// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingVisual.h"

// Sets default values
ABuildingVisual::ABuildingVisual()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMesh>(TEXT("SkeletalMesh"));
}

// Called when the game starts or when spawned
void ABuildingVisual::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingVisual::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

