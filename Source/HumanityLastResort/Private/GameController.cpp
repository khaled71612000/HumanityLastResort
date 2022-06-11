// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "Placeable.h"
#include "DrawDebugHelpers.h"
#include "PlacementInterface.h"
#include "SPSubsystem.h"
#include "SelectionSubsystem.h"
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
	SelectionSubSystem = GetWorld()->GetSubsystem<USelectionSubsystem>();
	FoundGrid = UGameplayStatics::GetActorOfClass(GetWorld(), ANewGrid::StaticClass());

}
void AGameController::Tick(float dt) {
	Super::Tick(dt);

	FVector start, dir;
	DeprojectMousePositionToWorld(start, dir);
	const FVector end = start + dir * 10000.0f;
	const FPlane plane{
	{FVector::ZeroVector},
	{0.f,0.f,1.f}
	};
	 FVector intersect = FMath::LinePlaneIntersection(start, end, plane);
	 intersect.Z = 100;

	FHitResult Hit;
	FCollisionQueryParams TraceParams;

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, start, end, ECC_Visibility, TraceParams);

	TArray<AActor*> actorPtrs;

	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UPlacementInterface::StaticClass(), actorPtrs);

	ANewGrid* GridPtr;

	if (actorPtrs.Num() != 0) {
		for (AActor* actor : actorPtrs) {
			IPlacementInterface* current = Cast<IPlacementInterface>(actor);
			if (current) {
				if (FoundGrid) {
					GridPtr = Cast<ANewGrid>(FoundGrid);
					if (GridPtr) {
						if (bHit) {
							HitBuilding = Hit;
							GridPtr->GetClosestPosition(intersect);
							current->MouseMove(GridPtr->GetClosestPosition(intersect));
						}
					}
				}
			}
		}
	}
}


void AGameController::OnLeftMouseRelease()
{
	SPSubsystem->OnLeftMouseRelease();
}

void AGameController::OnLeftMouseClicked()
{
	if(HitBuilding.GetActor())
	SelectionSubSystem->TrySelect(HitBuilding);
}

void AGameController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindKey(FKey{ "LeftMouseButton" }, EInputEvent::IE_Released, this, &AGameController::OnLeftMouseRelease);
	InputComponent->BindKey(FKey{ "LeftMouseButton" }, EInputEvent::IE_Pressed, this, &AGameController::OnLeftMouseClicked);

}


