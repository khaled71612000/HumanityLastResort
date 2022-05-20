// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Alien.generated.h"

enum State {
	Idle, Assigned, Leaving
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
	State AlienState;
	class UNeedComponent* NeedToExcute;

	void GetTask();
	void ExecuteTask();

};
