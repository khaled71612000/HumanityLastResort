// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraPawn.generated.h"

UCLASS()
class HUMANITYLASTRESORT_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "BuildTransform")
		void RotateToken(float value);

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY()
		USceneComponent* RootScene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;
		UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Panning")
	float CamSpeed = 8;

	APlayerController* Player;
	FVector GetCameraPanDirecton();

	UPROPERTY(EditAnywhere, Category = "Panning")
	float Margin = 50;
	int32 ScreenSizeX;
	int32 ScreenSizeY;

	

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OrbitRotate(float Value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float orbitSpeed = 1;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveForward(float Value);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveRight(float Value);
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UPawnMovementComponent* PawnMovementComponent;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UFloatingPawnMovement* FloatingPawnMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildTransform")
		class ABuildingsActors* SelectedToken;


};
