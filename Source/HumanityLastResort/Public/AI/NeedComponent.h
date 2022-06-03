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
	float MaxCapacity;

	UPROPERTY(Transient)
	float CurValue;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float DecayRate;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float TaskTime;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABuilding> Building;

	UPROPERTY(Transient)
	class UNeedSatisfactionTask* Task;

private:
	void OnRegister() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	void StartDecreasingValue();
	void DecreaseValue();
		
};
