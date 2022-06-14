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
	void GetCurrentMousePosition();
	void GetCurrentBuilding(const FVector& intersect);
	void BeginPlay() override;
	void SetupInputComponent()override;

	void OnLeftMouseRelease();
	void OnLeftMouseClicked();

	class USPSubsystem* SPSubsystem;
	class USelectionSubsystem* SelectionSubSystem;
	FVector start, dir, end;
	AActor* FoundGrid;
	FVector intersect;
	class ANewGrid* GridPtr;
	const FPlane plane{
	{ FVector::ZeroVector },
	{ 0.f,0.f,1.f }
	};

};
