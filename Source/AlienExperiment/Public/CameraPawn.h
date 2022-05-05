// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraPawn.generated.h"

UCLASS()
class ALIENEXPERIMENT_API ACameraPawn : public APawn
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
	UPROPERTY()
		APlayerController* Player;
	UFUNCTION()
		FVector GetCameraPanDirecton();
	UPROPERTY()
		float Margin = 15;

	UPROPERTY()
	int32 ScreenSizeX;

	UPROPERTY()
	int32 ScreenSizeY;

	UPROPERTY(EditAnywhere)
		float CamSpeed = 4;

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
