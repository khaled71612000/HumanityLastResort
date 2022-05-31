// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "AICharacterBase.generated.h"

UCLASS()
class HUMANITYLASTRESORT_API AAICharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	int32 NotHungry;
	int32 NotSleepy;

	TArray<AActor*> Resturants;
	TArray<AActor*> Hotels;

	bool GoingToResturant;
	bool GoingToHotel;


public:
	// Sets default values for this character's properties
	AAICharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GettingHungry();
	void GettingSleepy();

private:
	void ChangeNotHungryAttr();
	void ChangeNotSleepyAttr();

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveToResturant();
	void MoveToHotel();
	
};
