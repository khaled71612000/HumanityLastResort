// Fill out your copyright notice in the Description page of Project Settings.


#include "AISplinePathController.h"

const int HEIGHT = 250;
const int MAXPOINTS = 5000;
FVector pathPointLocaton[MAXPOINTS];
int splinePointer = 1;
int totalSplinePoints = 0;

void AAISplinePathController::BeginPlay() {
	Super::BeginPlay();

	GetSplinePoint();
	MoveToLocation(pathPointLocaton[splinePointer]);
}


void AAISplinePathController::GetSplinePoint() {
	for (TObjectIterator<USplineComponent> SplineComponent; SplineComponent; ++SplineComponent) {
		int NumberOfSplinePoints = SplineComponent->GetNumberOfSplinePoints();
		float totalLength = SplineComponent->GetSplineLength();
		float currentLength = 0;

		int itemSpaceing = 5; //spaciinig between tems spawned
		int SampleLength = 150; //we will save the spline every xx units

		FString SplineName = SplineComponent->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("SPLINE FOUND : %s"), *SplineName));

		if (SplineName == "PathSpline") {
			int splinePointCount = 0;
			while (currentLength < totalLength) {
				FTransform SplinePontTransform = SplineComponent->GetTransformAtDistanceAlongSpline(currentLength, ESplineCoordinateSpace::World);
				currentLength += SampleLength; //increast current length for next sample
				pathPointLocaton[splinePointCount] = SplinePontTransform.GetLocation();
				splinePointCount++;
			}
			totalSplinePoints = splinePointCount;
		}

	}
}

void AAISplinePathController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	splinePointer++;

	if (splinePointer >= totalSplinePoints) {
		splinePointer = 1;
	}
	MoveToLocation(pathPointLocaton[splinePointer]);

}