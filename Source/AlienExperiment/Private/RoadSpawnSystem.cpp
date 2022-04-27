// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadSpawnSystem.h"
#include "Components/SplineComponent.h"

// Sets default values
ARoadSpawnSystem::ARoadSpawnSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Our spline Component"));
	if (SplineComponent)
	{
		RootComponent = SplineComponent;
	}
}

void ARoadSpawnSystem::OnConstruction(const FTransform& Transform)
{
	// this condition will be true if the Start Road mesh hasn't been assigned in the editor and if there is no mesh assinged there is no point runnning the code
	if (StartRoad == nullptr)
	{
		return;
	}

	for (int index = 0; index <= FGenericPlatformMath::TruncToInt(SplineComponent->GetSplineLength() / RoadWidth); index++)
	{
		USplineMeshComponent* SplineMeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());

		// allowing our mesh to move with our spline
		SplineMeshComponent->SetMobility(EComponentMobility::Movable);
		// Letting our Engine know that our mesh component is being Created in the construction script 
		SplineMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		// Registering our component with the world
		SplineMeshComponent->RegisterComponentWithWorld(GetWorld());
		// Attaching spline mesh to our spline 
		SplineMeshComponent->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);

		// Getting the necessary inputs to pass in to our SetStartAndEnd
		const FVector StartPos = SplineComponent->GetLocationAtDistanceAlongSpline(index * RoadWidth, ESplineCoordinateSpace::Local);
		const FVector StartTangent = SplineComponent->GetTangentAtDistanceAlongSpline(index * RoadWidth, ESplineCoordinateSpace::Local);
		const FVector EndPos = SplineComponent->GetLocationAtDistanceAlongSpline((index + 1) * RoadWidth, ESplineCoordinateSpace::Local);
		const FVector EndTangent = SplineComponent->GetTangentAtDistanceAlongSpline((index + 1) * RoadWidth, ESplineCoordinateSpace::Local);
		SplineMeshComponent->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent, true);
		// sets the collisions of our mesh 
		SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		// To Allow for a more flexible design since user can define what there forward axis is .
		SplineMeshComponent->SetForwardAxis(ForwardAxis, true);
		// choosing what mesh to render
		if (StartRoad && index == 0)
		{
			SplineMeshComponent->SetStaticMesh(StartRoad);
		}
		else if (EndRoad && (index == FGenericPlatformMath::TruncToInt(SplineComponent->GetSplineLength() / RoadWidth)))
		{
			SplineMeshComponent->SetStaticMesh(EndRoad);
		}
		else
		{
			if (MiddleRoad)
			{
				SplineMeshComponent->SetStaticMesh(MiddleRoad);
			}
		}
	}
}

