// Fill out your copyright notice in the Description page of Project Settings.

#include "Placeable.h"
#include "CameraPawn.h"
#include "Kismet\KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "CellActor.h"
#include "Math/UnrealMathUtility.h"
#include "RunTime\Engine\Classes\Kismet\GameplayStatics.h"
#include "AI/Alien.h"
#include "Buildings/BuildingSubsystem.h"
#include "SelectionSubsystem.h"
#include "Road.h"
#include "RoadSubsystem.h"
#include "Components/SkeletalMeshComponent.h"

APlaceable::APlaceable()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = SkeletalMeshComponent;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(SkeletalMeshComponent);

}

void APlaceable::BeginPlay()
{
	Super::BeginPlay();
	world = GetWorld();
	BuildingSubsystem = world->GetSubsystem<UBuildingSubsystem>();
	RoadSubsystem = world->GetSubsystem<URoadSubsystem>();
	if (SkeletalMeshComponent)
		SkeletalMeshComponent->OnClicked.AddDynamic(this, &APlaceable::OnClicked);

	oldPos = GetActorLocation();

	FTimerHandle StatManager;
	if (!isDragging && SkeletalMeshComponent) {
		SkeletalMeshComponent->SetMobility(EComponentMobility::Static);
		SceneComponent->SetMobility(EComponentMobility::Static);
	}

	if (SkeletalMeshComponent)
		UKismetSystemLibrary::GetComponentBounds(SkeletalMeshComponent, OriginSklet, HalfBoxSklet, sphereRad);

	SelectionSubSystem = world->GetSubsystem<USelectionSubsystem>();
	HalfBoxSklet.Z = 1;
}


void APlaceable::OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	isDragging = true;
	if (SkeletalMeshComponent) {

		SkeletalMeshComponent->SetMobility(EComponentMobility::Movable);
		SceneComponent->SetMobility(EComponentMobility::Movable);

	}
}

void APlaceable::LockPosition(bool block)
{
	if (SkeletalMeshComponent) {
		if (SkeletalMeshComponent->GetBodyInstance()->bLockXTranslation) {
			SkeletalMeshComponent->SetMobility(EComponentMobility::Movable);
			SceneComponent->SetMobility(EComponentMobility::Movable);
		}
	}
	else {
		if (SkeletalMeshComponent) {
			SkeletalMeshComponent->SetMobility(EComponentMobility::Static);
			SceneComponent->SetMobility(EComponentMobility::Static);
		}
	}
}


void APlaceable::ResetRotation()
{
	SkeletalMeshComponent->SetMobility(EComponentMobility::Movable);
	SceneComponent->SetMobility(EComponentMobility::Movable);
	SetActorRotation(FRotator::ZeroRotator);
	SkeletalMeshComponent->SetMobility(EComponentMobility::Static);
	SceneComponent->SetMobility(EComponentMobility::Static);
}


void APlaceable::MouseMove(FVector position)
{
	if (isDragging)
	{
		ClearFloor();

		if (ARoad* isRoad = Cast<ARoad>(this)) {
			RoadSubsystem->UpdateRoads();
		}

		FVector origin, boxExtent;
		GetActorBounds(false, origin, boxExtent);
		boxExtent.Z = 1.f;

		this->SetActorLocation(position);
		MyPawn = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<ACameraPawn>();
		if (MyPawn)
			MyPawn->SelectedToken = this;

		FVector Start = position;
		Start.Z += 1;

		FVector End = Start;
		End.Z += 100;

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		TArray<FHitResult> HitResult;

		bool BoxHit = UKismetSystemLibrary::BoxTraceMulti(world, Start, End,
			HalfBoxSklet,
			GetActorRotation(), UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false, ActorsToIgnore, EDrawDebugTrace::None, HitResult,
			true, FLinearColor::Red, FLinearColor::Green, -1
		);

		if(!BoxHit)
			oldPos = position;


		if (BoxHit) {
			this->SetActorLocation(oldPos);
		}
	}
}



void APlaceable::MouseRelease()
{
	isDragging = false;
	if (MyPawn)
		MyPawn->SelectedToken = nullptr;
	oldPos = GetActorLocation();
	if (!isDragging) {
		if (SkeletalMeshComponent) {
			SkeletalMeshComponent->SetMobility(EComponentMobility::Static);
			SceneComponent->SetMobility(EComponentMobility::Static);
		}
	}
}


void APlaceable::ClearFloor()
{
	FVector Start = GetActorLocation();
	FVector End = ((GetActorUpVector() * 80.f) + Start);

	FVector origin, boxExtent;
	GetActorBounds(false, origin, boxExtent);
	boxExtent.Z = 2;
	boxExtent *= 1.6;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	TArray<FHitResult> HitArray;

	bool Hiting = UKismetSystemLibrary::BoxTraceMulti(world, Start, End, boxExtent,
		GetActorRotation(), UEngineTypes::ConvertToTraceType(ECC_Pawn),
		false, ActorsToIgnore, EDrawDebugTrace::None, HitArray,
		true, FLinearColor::Green, FLinearColor::Yellow, 0.1f
	);

	if (Hiting) {
		for (auto& NPC : HitArray)
		{
			AAlien* NPCHit = Cast<AAlien>(NPC.GetActor());
			if (NPCHit) {
				NPCHit->SetActorLocation(RespawnLoc, true);
			}
		}
	}
}

void APlaceable::DestroyBuildingActor()
{
	if (Cast<ABuilding>(this))
		BuildingSubsystem->RemoveBuilding(Cast<ABuilding>(this));

	else if (Cast<ARoad>(this))
		RoadSubsystem->RemoveRoad(Cast<ARoad>(this));

	if (IISelectionHandler* CurrentSelect = Cast<IISelectionHandler>(this))
		SelectionSubSystem->RemoveSelectionHandler(CurrentSelect);

	Destroy();
}
