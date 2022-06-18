// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Alien.generated.h"

enum State {
	Idle, Assigned, Arrived, Waiting, Leaving, Moving, Wandering
};

struct Range {
	int32 from;
	int32 to;
};


UCLASS()
class HUMANITYLASTRESORT_API AAlien : public ACharacter
{
	GENERATED_BODY()

public:
	AAlien();

protected:
	virtual void BeginPlay() override;

public:
	bool isDancing;
	int32 Mood;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 GoodMoodVal;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 BadMoodVal;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 NumOfTasks;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 NumOfFailedTasks;

	int32 AlienType;
	State AlienState;
	int32 CurTasks;
	int32 CurFailedTasks;

	UPROPERTY()
	class UNeedSatisfactionTask* Task;

	UPROPERTY()
	class UAlienSubsystem* AlienSubsystem;

	UPROPERTY()
	TArray<class UNeedComponent*> Needs;

	void TryGetTask();
	void GoToTask();
	void DoTask();
	void Wander();
	void Leave();
	void ChangeMood(int MoodVal);
	void RemoveAlien();
	void ResetAlienNeeds();

	UFUNCTION(BlueprintCallable)
		bool GetisDancing();
};
