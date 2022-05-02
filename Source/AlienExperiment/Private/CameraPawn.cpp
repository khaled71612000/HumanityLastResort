// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
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
	SpringArm->TargetArmLength = 1500.f;

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
	//Player->DefaultMouseCursor = EMouseCursor::Crosshairs;
	FInputModeGameAndUI inputMode;
	inputMode.SetHideCursorDuringCapture(false);
	Player->SetInputMode(inputMode);
	
}

FVector ACameraPawn::GetCameraPanDirecton() {
	float MousePosX;
	float MousePosY;
	
	float CamDirectonX = 0;
	float CamDirectonY = 0;


	Player->GetMousePosition(MousePosX, MousePosY);

	if (MousePosX <= Margin) {
		CamDirectonY = -1;
	}

	if (MousePosY <= Margin) {
		CamDirectonX = 1;
	}

	if (MousePosX >= ScreenSizeX - Margin) {
		CamDirectonY = 1;
	}

	if (MousePosY >= ScreenSizeY - Margin) {
		CamDirectonX = -1;
	}

	return FVector(CamDirectonX, CamDirectonY, 0);
}

void ACameraPawn::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ACameraPawn::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
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

}

