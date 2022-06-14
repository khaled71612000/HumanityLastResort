// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Placeable.h"
#include "Road.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API ARoad : public APlaceable
{
	GENERATED_BODY()
public:

	ARoad();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PathWays")
		class UStaticMeshComponent* PathWayNorth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PathWays")
		class UStaticMeshComponent* PathWayEast;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PathWays")
		class UStaticMeshComponent* PathWaySouth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PathWays")
		class UStaticMeshComponent* PathWayWest;
	UFUNCTION(BlueprintCallable)
		void UpdateSideOfRoadTile();
};
	