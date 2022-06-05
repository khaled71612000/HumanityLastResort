// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "Placeable.h"
#include "DrawDebugHelpers.h"
#include "PlacementInterface.h"
#include "SPSubsystem.h"
#include "NewGrid.h"
#include "CellActor.h"
#include "RunTime\Engine\Classes\Kismet\GameplayStatics.h"


AGameController::AGameController() {
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	DefaultMouseCursor = EMouseCursor::Hand;

}

void AGameController::BeginPlay()
{
	SPSubsystem = GetWorld()->GetSubsystem<USPSubsystem>();

}
void AGameController::Tick(float dt) {
	Super::Tick(dt);

	FVector start, dir;
	DeprojectMousePositionToWorld(start, dir);
	const FVector end = start + dir * 10000.0f;


	FHitResult Hit;
	FCollisionQueryParams TraceParams;

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, start, end, ECC_Visibility, TraceParams);

	FVector origin;
	FVector boundsExtent;
	ACellActor* Tile;
	if (bHit) {
		Tile = Cast<ACellActor>(Hit.GetActor());
		if (Tile) {
			Tile->GetActorBounds(false, origin, boundsExtent);
		}
		origin.X -= 195;
		origin.Y -= 195;
		origin.Z += 100.f;
	}

	TArray<AActor*> actorPtrs;

	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UPlacementInterface::StaticClass(), actorPtrs);

	if (actorPtrs.Num() != 0) {
		for (AActor* actor : actorPtrs) {

			IPlacementInterface* current = Cast<IPlacementInterface>(actor);

			if (current) {

				current->MouseMove(origin);
			}
		}
	}
}


void AGameController::OnLeftMouseRelease()
{
	SPSubsystem->OnLeftMouseRelease();
}

void AGameController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindKey(FKey{ "LeftMouseButton" }, EInputEvent::IE_Released, this, &AGameController::OnLeftMouseRelease);
}


