// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Alien.generated.h"

enum State {
	Idle, Assigned, Arrived, Waiting, Leaving
};

UCLASS()
class HUMANITYLASTRESORT_API AAlien : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAlien();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	int32 Mood;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	int32 GoodMoodVal;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	int32 BadMoodVal;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	int32 NumOfTasks;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	int32 NumOfFailedTasks;


	State AlienState;
	class UNeedComponent* NeedToExcute;
	class UAlienSubsystem* AlienSubsystem;

	void GetTask();
	void GoToTask();
	void DoTask();
	void Leave();
	void ChangeMood(int MoodVal);
};
