// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Placeable.h"
#include "Building.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API ABuilding : public APlaceable
{
	GENERATED_BODY()
protected:
	ABuilding();
public:
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 Capacity;
	UPROPERTY(Transient)
		int32 CurOccupants;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 Profit;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 Loss;

protected:
	virtual void BeginPlay() override;

public:
	class UEconomySubsystem* EconomySubsystem;
	void AddProfit();
	void SubtractLoss();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Collider")
	class USphereComponent* BuildingCollision;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
