// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class HUMANITYLASTRESORT_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:	
	ACameraPawn();

	UPROPERTY()
		USceneComponent* RootScene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* CameraComp;

	UPROPERTY(Category = "Panning", EditAnywhere)
		float CamSpeed = 8;
	UPROPERTY(Category = "Panning", EditAnywhere)
		float Margin = 50;
	UPROPERTY()
	APlayerController* Player;

	UPROPERTY()
	int32 ScreenSizeX;
	UPROPERTY()
	int32 ScreenSizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float orbitSpeed = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float CameraPitchSpeed = 1;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UPawnMovementComponent* PawnMovementComponent;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UFloatingPawnMovement* FloatingPawnMovement;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildTransform")
		class APlaceable* SelectedToken;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void OrbitRotate(float Value);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void CameraPitch(float Value);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveForward(float Value);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveRight(float Value);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		FVector GetCameraPanDirecton();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	virtual void BeginPlay() override;

	UFUNCTION(Category = "BuildTransform", BlueprintCallable)
		void RotateToken(float value);

};
