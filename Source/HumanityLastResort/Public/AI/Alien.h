// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Alien.generated.h"

enum State {
	Idle, Assigned, Arrived, Waiting, Leaving
};

struct Range {
	int32 from;
	int32 to;
};

struct AlienNeedsValue {
	Range DecayRate;
	Range TimeSpent;
};

struct AlienAttributes {
	Range GoodMoodVal;
	Range BadMoodVal;
	Range NumOfTasks;
	Range NumOfFailedTasks;
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
	class UNeedSatisfactionTask* Task;
	class UAlienSubsystem* AlienSubsystem;
	TArray<class UNeedComponent*> Needs;

	bool TryGetTask();
	void GoToTask();
	void DoTask();
	void Leave();
	void ChangeMood(int MoodVal);
	void SetAlienNeedsValues(TArray<AlienNeedsValue*>& NeedsValues);
	void SetAlienAttributes(AlienAttributes AlienAttributes);
	void AddAlienToPool();
	virtual void CallSetAlienNeedsValues();
	virtual void CallSetAlienAttributes();

	UFUNCTION(BlueprintCallable)
		bool GetisDancing();
};
