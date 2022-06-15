// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NeedComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUMANITYLASTRESORT_API UNeedComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNeedComponent();

	UPROPERTY(Transient)
	int32 MaxCapacity;

	UPROPERTY(Transient)
	int32 CurValue;

	UPROPERTY(Transient)
	int32 DecayRate;

	UPROPERTY(Transient)
	int32 TaskTime;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 DecayRateFROM;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 DecayRateTO;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 TaskTimeFROM;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 TaskTimeTO;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	int32 Threshold;

	UPROPERTY(EditDefaultsOnly, Category = "Building")
	int32 BuildingType;

private:
	void OnRegister() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	void StartDecreasingValue();
	void DecreaseValue();
		
};
