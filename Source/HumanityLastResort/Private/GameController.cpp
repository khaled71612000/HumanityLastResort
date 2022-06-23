// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "Placeable.h"
#include "DrawDebugHelpers.h"
#include "PlacementInterface.h"
#include "SPSubsystem.h"
#include "SelectionSubsystem.h"
#include "NewGrid.h"
#include "CellActor.h"
#include "Road.h"
#include "RunTime\Engine\Classes\Kismet\GameplayStatics.h"


AGameController::AGameController() {
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	DefaultMouseCursor = EMouseCursor::Hand;
}

void AGameController::BeginPlay()
{
	world = GetWorld();
	SPSubsystem = world->GetSubsystem<USPSubsystem>();
	SelectionSubSystem = world->GetSubsystem<USelectionSubsystem>();
	FoundGrid = UGameplayStatics::GetActorOfClass(world, ANewGrid::StaticClass());

	if (FoundGrid) {
		GridPtr = Cast<ANewGrid>(FoundGrid);
	}
}
void AGameController::Tick(float dt) {
	Super::Tick(dt);
	GetCurrentMousePosition();
	GetCurrentBuilding(intersect);
}

void AGameController::GetCurrentMousePosition()
{
	DeprojectMousePositionToWorld(start, dir);
	end = start + dir * 100000.0f;

	intersect= FMath::LinePlaneIntersection(start, end, plane);
	intersect.Z = 100;
}

void AGameController::GetCurrentBuilding(const FVector& intersectPoint)
{
	TArray<AActor*> actorPtrs;

	UGameplayStatics::GetAllActorsWithInterface(world,
		UPlacementInterface::StaticClass(), actorPtrs);

	if (actorPtrs.Num() != 0) {
		for (AActor* actor : actorPtrs) {
			IPlacementInterface* current = Cast<IPlacementInterface>(actor);
			if (current) {
				if (GridPtr) {
					GridPtr->GetClosestPosition(intersectPoint);
					current->MouseMove(GridPtr->GetClosestPosition(intersectPoint));
				}
			}
		}
	}
}


void AGameController::OnLeftMouseRelease()
{
	SPSubsystem->OnLeftMouseRelease();

	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	bool bHit = world->LineTraceSingleByChannel(Hit, start, end, ECC_Visibility, TraceParams);
	SelectionSubSystem->DeSelect(Hit);
}

void AGameController::OnLeftMouseClicked()
{
	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	bool bHit = world->LineTraceSingleByChannel(Hit, start, end, ECC_Visibility, TraceParams);

	if (Hit.GetActor()) {
		SelectionSubSystem->TrySelect(Hit);
	}
}

void AGameController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindKey(FKey{ "LeftMouseButton" }, EInputEvent::IE_Released, this, &AGameController::OnLeftMouseRelease);
	InputComponent->BindKey(FKey{ "LeftMouseButton" }, EInputEvent::IE_Pressed, this, &AGameController::OnLeftMouseClicked);
}


