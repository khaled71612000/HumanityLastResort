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

	//StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	//StaticMeshComponent->SetupAttachment(SkeletalMeshComponent);


	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	//SceneComponent->SetupAttachment(StaticMeshComponent);
	SceneComponent->SetupAttachment(SkeletalMeshComponent);

	//StaticMeshComponent->bIgnoreRadialForce = true;
	//StaticMeshComponent->bIgnoreRadialImpulse = true;
	//StaticMeshComponent->SetLinearDamping(1.f);
	//StaticMeshComponent->SetAngularDamping(1.f);
}

void APlaceable::BeginPlay()
{
	Super::BeginPlay();
	BuildingSubsystem = GetWorld()->GetSubsystem<UBuildingSubsystem>();
	RoadSubsystem = GetWorld()->GetSubsystem<URoadSubsystem>();

	//StaticMeshComponent->OnClicked.AddDynamic(this, &APlaceable::OnClicked);
	if(SkeletalMeshComponent)
	SkeletalMeshComponent->OnClicked.AddDynamic(this, &APlaceable::OnClicked);

	oldPos = GetActorLocation();

	FTimerHandle StatManager;
			if (!isDragging && SkeletalMeshComponent) {
				//SkeletalMeshComponent->GetBodyInstance()->bLockXTranslation = true;
				//SkeletalMeshComponent->GetBodyInstance()->bLockYTranslation = true;
				//SkeletalMeshComponent->GetBodyInstance()->bLockZTranslation = true;
				//SkeletalMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
				SkeletalMeshComponent->SetMobility(EComponentMobility::Static);
				SceneComponent->SetMobility(EComponentMobility::Static);
			}

	/*StaticMeshComponent->GetLocalBounds(Min, Max);*/
			if(SkeletalMeshComponent)
	UKismetSystemLibrary::GetComponentBounds(SkeletalMeshComponent, OriginSklet , HalfBoxSklet , sphereRad);
	//NewBoxSize = (Max - Min) / 2;
	//NewBoxSize.Z = 0;
	SelectionSubSystem = GetWorld()->GetSubsystem<USelectionSubsystem>();
	HalfBoxSklet.Z = 1;
}


void APlaceable::OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	isDragging = true;
	//UE_LOG(LogTemp, Error, TEXT("HELLO"));
	if (SkeletalMeshComponent) {
	//SkeletalMeshComponent->GetBodyInstance()->bLockXTranslation = false;
	//SkeletalMeshComponent->GetBodyInstance()->bLockYTranslation = false;
	//SkeletalMeshComponent->GetBodyInstance()->bLockZTranslation = false;
	//SkeletalMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
	SkeletalMeshComponent->SetMobility(EComponentMobility::Movable);
	SceneComponent->SetMobility(EComponentMobility::Movable);

	}
}

void APlaceable::LockPosition(bool block)
{
		if (SkeletalMeshComponent) {
	if (SkeletalMeshComponent->GetBodyInstance()->bLockXTranslation) {

			//SkeletalMeshComponent->GetBodyInstance()->bLockXTranslation = false;
			//SkeletalMeshComponent->GetBodyInstance()->bLockYTranslation = false;
			//SkeletalMeshComponent->GetBodyInstance()->bLockZTranslation = false;
			//SkeletalMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
			SkeletalMeshComponent->SetMobility(EComponentMobility::Movable);
			SceneComponent->SetMobility(EComponentMobility::Movable);

		}
	}
	else {
			if (SkeletalMeshComponent) {

				//SkeletalMeshComponent->GetBodyInstance()->bLockXTranslation = true;
				//SkeletalMeshComponent->GetBodyInstance()->bLockYTranslation = true;
				//SkeletalMeshComponent->GetBodyInstance()->bLockZTranslation = true;
				//SkeletalMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
				SkeletalMeshComponent->SetMobility(EComponentMobility::Static);
				SceneComponent->SetMobility(EComponentMobility::Static);

			}
	}
}


void APlaceable::ResetRotation()
{
	SetActorRotation(FRotator::ZeroRotator);
}


void APlaceable::MouseMove(FVector position)
{
	if (isDragging)
	{
		ClearFloor();
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

		bool BoxHit = UKismetSystemLibrary::BoxTraceMulti(GetWorld(), Start, End,
			HalfBoxSklet,
			GetActorRotation(), UEngineTypes::ConvertToTraceType(ECC_Pawn),
			false, ActorsToIgnore, EDrawDebugTrace::None, HitResult,
			true, FLinearColor::Red, FLinearColor::Green, -1
		);

		if (BoxHit) {
				this->SetActorLocation(oldPos);
		}
	}
}

void APlaceable::ClearFloor()
{
	FVector Start = GetActorLocation();
	FVector End = ((GetActorUpVector() * 80.f) + Start);

	FVector origin, boxExtent;
	GetActorBounds(false, origin, boxExtent);
	boxExtent.Z = 1.f;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	TArray<FHitResult> HitArray;

	bool Hiting = UKismetSystemLibrary::BoxTraceMulti(GetWorld(), Start, End, boxExtent,
		GetActorRotation(), UEngineTypes::ConvertToTraceType(ECC_Visibility),
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


void APlaceable::MouseRelease()
{
	isDragging = false;
	if (MyPawn)
		MyPawn->SelectedToken = nullptr;
	oldPos = GetActorLocation();
			if (!isDragging) {
				if (SkeletalMeshComponent) {

					//SkeletalMeshComponent->GetBodyInstance()->bLockXTranslation = true;
					//SkeletalMeshComponent->GetBodyInstance()->bLockYTranslation = true;
					//SkeletalMeshComponent->GetBodyInstance()->bLockZTranslation = true;
					//SkeletalMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
					SkeletalMeshComponent->SetMobility(EComponentMobility::Static);
					SceneComponent->SetMobility(EComponentMobility::Static);

				}
			}
}

void APlaceable::DestroyBuildingActor()
{
	if (Cast<ABuilding>(this))
		BuildingSubsystem->RemoveBuilding(Cast<ABuilding>(this));

	else if (Cast<ARoad>(this))
		RoadSubsystem->RemoveRoad(Cast<ARoad>(this));

	if(IISelectionHandler* CurrentSelect = Cast<IISelectionHandler>(this))
		SelectionSubSystem->RemoveSelectionHandler(CurrentSelect);

	Destroy();
}
