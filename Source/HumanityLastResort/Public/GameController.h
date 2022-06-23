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

	FVector start, dir, end;
	AActor* FoundGrid;
	FVector intersect;
	const FPlane plane{
	{ FVector::ZeroVector },
	{ 0.f,0.f,1.f }
	};

	UPROPERTY()
		class USPSubsystem* SPSubsystem;
	UPROPERTY()
		class USelectionSubsystem* SelectionSubSystem;
	UPROPERTY()
		class ANewGrid* GridPtr;
	 UWorld*  world;
	void Tick(float dt) override;
	void GetCurrentMousePosition();
	void GetCurrentBuilding(const FVector& intersect);
	void BeginPlay() override;
	void SetupInputComponent()override;
	void OnLeftMouseRelease();
	void OnLeftMouseClicked();
};
