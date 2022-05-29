// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "BuildingsActors.h"
#include "DrawDebugHelpers.h"
#include "PlacementInterface.h"
#include "SPSubsystem.h"
#include "NewGrid.h"
#include <CellActor.h>
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

	/*const FPlane plane{
		{FVector::ZeroVector},
		{0.f,0.f,1.f}
	};*/
	//const auto intersect = FMath::LinePlaneIntersection(start, end, plane);

	/*DrawDebugLine(GetWorld(), start, end, FColor::Orange, false, 0.1f);
	DrawDebugSphere(GetWorld(), intersect, 5, 50, FColor::Red, true);*/

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
		//const auto middleIntersect = Hit.GetActor()->
		origin.X -= 195;
		origin.Y -= 195;
		origin.Z += 100.f;
		//DrawDebugSphere(GetWorld(), origin, 5, 50, FColor::Red, true , 5);

	}

	TArray<AActor*> actorPtrs;
	//AActor* FoundGrid;
	//ANewGrid* GridPtr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildingsActors::StaticClass(), actorPtrs);
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UPlacementInterface::StaticClass(), actorPtrs);

	//FoundGrid = UGameplayStatics::GetActorOfClass(GetWorld(), ANewGrid::StaticClass());

	//UE_LOG(LogTemp, Warning, TEXT("HERE Clicked %d"),actorPtrs.Num());
	if (actorPtrs.Num() != 0) {
		for (AActor* actor : actorPtrs) {

			IPlacementInterface* current = Cast<IPlacementInterface>(actor);

			if (current) {
				//	if (FoundGrid) {
						//GridPtr = Cast<ANewGrid>(FoundGrid);
					//	if (GridPtr) {
							//GridPtr->GetClosestPosition(origin);
							//current->MouseMove(GridPtr->GetClosestPosition(intersect));
						//}
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


