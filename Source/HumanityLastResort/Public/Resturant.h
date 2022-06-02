// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingsActors.h"
#include "Resturant.generated.h"

UCLASS()
class HUMANITYLASTRESORT_API AResturant : public ABuildingsActors
{
	GENERATED_BODY()
public:

	AResturant(const FObjectInitializer& objectInitializer);

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class USphereComponent* RestCollision;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
