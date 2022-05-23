// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
//#include "AIControllerBase.h"
#include "AICharacterBase.generated.h"

enum TaskStates {
	Idle, Assigned, Moving, Failed
};

UCLASS()
class ALIENEXPERIMENT_API AAICharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	TaskStates TaskState;

public:
	int32 NotHungry;
	int32 NotSleepy;

	bool isHungry;
	bool isSleepy;

	bool DoingTask;
	int TaskInd;

	TMap<int32, AActor*> Resturants;
	TMap<int32, AActor*> Hotels;

public:
	AAICharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	FTimerHandle HungryManager;
	FTimerHandle SleepyManager;

private:
	void GettingHungry();
	void GettingSleepy();
	void ChangeNotHungryAttr();
	void ChangeNotSleepyAttr();

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveToResturant();
	void MoveToHotel();

public:	
	TArray<bool*> AIState;
	TArray<int32*> AIAttributes;
	typedef void (AAICharacterBase::* Action)();
	TArray<Action> Actions;	
};
