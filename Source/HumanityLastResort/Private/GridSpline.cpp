// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSpline.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"

AGridSpline::AGridSpline()
{
	PrimaryActorTick.bCanEverTick = false;
	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");

}

void AGridSpline::AddMeshToSplinePoint(int const& SplinePoint)
{
	if (StaticMeshREF && MaterialREF) {
		UStaticMeshComponent* NewMeshComponent = NewObject<UStaticMeshComponent>(this);
		NewMeshComponent->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepWorldTransform);
		NewMeshComponent->RegisterComponent();
		NewMeshComponent->SetStaticMesh(StaticMeshREF);
		NewMeshComponent->SetMaterial(0, MaterialREF);
		NewMeshComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
		NewMeshComponent->SetWorldLocation(SplineComponent->GetLocationAtSplinePoint(SplinePoint, ESplineCoordinateSpace::World));
	}
}

void AGridSpline::BeginPlay()
{
	Super::BeginPlay();
	
}



