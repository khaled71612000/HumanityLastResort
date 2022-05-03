// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "Hotel.generated.h"

/**
 * 
 */
UCLASS()
class ALIENEXPERIMENT_API AHotel : public ABuildingBase
{
	GENERATED_BODY()

public:
	AHotel(const FObjectInitializer& objectInitializer);

	UPROPERTY(VisibleAnyWhere, Category = "Trigger Capsule")
	class USphereComponent* HotelCollision;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
