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

	UPROPERTY()
	APlayerController* Player;

	UPROPERTY()
	int32 ScreenSizeX;
	UPROPERTY()
	int32 ScreenSizeY;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UPawnMovementComponent* PawnMovementComponent;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		class UFloatingPawnMovement* FloatingPawnMovement;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildTransform")
		class APlaceable* SelectedToken;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	virtual void BeginPlay() override;

	UFUNCTION(Category = "BuildTransform", BlueprintCallable)
		void RotateToken(float value);

};
