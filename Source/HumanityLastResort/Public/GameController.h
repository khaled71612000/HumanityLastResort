// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameController.generated.h"

UCLASS()
class HUMANITYLASTRESORT_API AGameController : public APlayerController
{
	GENERATED_BODY()

public:
	AGameController();

protected:
	void Tick(float dt) override;
	void BeginPlay() override;
	void SetupInputComponent()override;

	void OnLeftMouseRelease();
	void OnLeftMouseClicked();
	class USPSubsystem* SPSubsystem;
	class USelectionSubsystem* SelectionSubSystem;
	FHitResult HitBuilding;
	
};
