// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"
#include "RoadSpawnSystem.generated.h"

UCLASS()
class ALIENEXPERIMENT_API ARoadSpawnSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoadSpawnSystem();

	// Sets default values for this actor's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		class USplineComponent* SplineComponent;
	UPROPERTY(EditAnywhere, Category = "Street Properties")
		float RoadWidth = 600.0f;
	void OnConstruction(const FTransform& Transform)override;
	// The meshes that get set in our editor 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Street Properties")
		UStaticMesh* StartRoad;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Street Properties")
		UStaticMesh* MiddleRoad;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Street Properties")
		UStaticMesh* EndRoad;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Street Properties")
		TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;

};
