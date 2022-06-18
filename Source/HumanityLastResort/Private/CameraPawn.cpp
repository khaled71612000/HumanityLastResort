// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include "Placeable.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));
	SpringArm->SocketOffset=FVector(-60, 0, 0);

	SpringArm->TargetArmLength = 3000.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	PawnMovementComponent = CreateDefaultSubobject<UPawnMovementComponent>(TEXT("Pawn Movement"));
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Float Movement"));


}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerController>(GetController());
	Player->GetViewportSize(ScreenSizeX, ScreenSizeY);

	Player->bShowMouseCursor = true;
	FInputModeGameAndUI inputMode;
	inputMode.SetHideCursorDuringCapture(false);
	Player->SetInputMode(inputMode);
}

FVector ACameraPawn::GetCameraPanDirecton() {
	/*float MousePosX;
	float MousePosY;

	float CamDirectonX = 0;
	float CamDirectonY = 0;


	Player->GetMousePosition(MousePosX, MousePosY);

	if (MousePosX < Margin) {
		CamDirectonY = -1;
	}

	if (MousePosY < Margin) {
		CamDirectonX = 1;
	}

	if (MousePosX > ScreenSizeX - Margin) {
		CamDirectonY = 1;
	}

	if (MousePosY > ScreenSizeY - Margin) {
		CamDirectonX = -1;
	}*/

	//return FVector(CamDirectonX, CamDirectonY, 0);
	return FVector(0, 0, 0);


}

void ACameraPawn::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ACameraPawn::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}
void ACameraPawn::RotateToken(float value) {
	if (SelectedToken) {

		auto const OriginalRotation = SelectedToken->GetActorRotation().GetDenormalized();
		float const Remainder = FMath::Fmod(OriginalRotation.Yaw, 90.f);

		/** If we have a Yaw that is greater than or equal to 360 degrees, use 0 instead */
		int Quotient = (OriginalRotation.Yaw > 337.5f ? 0 : OriginalRotation.Yaw) / 90.f;

		/**
		 * if our Yaw is close to 360 then don't upgrade the Quotient
		 * (lest we shoot past 45 and go to 90)
		 */
		if (Remainder >= 22.5f && OriginalRotation.Yaw < 337.5f)
		{
			++Quotient;
		}

		Quotient *= 90.f;

		if (value > 0)
		{
			Quotient += 90.f;
		}
		else if (value < 0)
		{
			Quotient -= 90.f;
			Quotient < 0 ? Quotient += 360 : Quotient;
		}


		auto NewRotation = FRotator(0.f, Quotient, 0.f);
		NewRotation.Normalize();

		SelectedToken->SetActorRotation(NewRotation);
		
	}
}
void ACameraPawn::OrbitRotate(float Value)
{
	AddActorWorldRotation(FRotator(0 , orbitSpeed * Value, 0));
}

void ACameraPawn::CameraPitch(float Value)
{
	float minClamp = 310.f;
	float maxClamp = 350.f;

	FRotator NewRotation = SpringArm->GetComponentRotation();
	NewRotation.Pitch = NewRotation.Pitch + CameraPitchSpeed * Value;
	NewRotation.Pitch = FMath::ClampAngle(NewRotation.Pitch, minClamp, maxClamp);

	SpringArm->SetWorldRotation(NewRotation);;
}
	
// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//AddActorWorldOffset(GetCameraPanDirecton() * CamSpeed);

}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ACameraPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACameraPawn::MoveRight);
	InputComponent->BindAxis("Orbit", this, &ACameraPawn::OrbitRotate);
	InputComponent->BindAxis("CameraPitch", this, &ACameraPawn::CameraPitch);

	InputComponent->BindAxis("Rotate", this, &ACameraPawn::RotateToken);

}

