// Fill out your copyright notice in the Description page of Project Settings.


#include "Placeable.h"
#include "CameraPawn.h"
#include "Kismet\KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "CellActor.h"
#include "Math/UnrealMathUtility.h"
#include "RunTime\Engine\Classes\Kismet\GameplayStatics.h"
#include "AI/Alien.h"



APlaceable::APlaceable()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMeshComponent;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(StaticMeshComponent);

	StaticMeshComponent->bIgnoreRadialForce = true;
	StaticMeshComponent->bIgnoreRadialImpulse = true;
	StaticMeshComponent->SetLinearDamping(1.f);
	StaticMeshComponent->SetAngularDamping(1.f);


}

void APlaceable::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->OnClicked.AddDynamic(this, &APlaceable::OnClicked);
	oldPos = GetActorLocation();

	FTimerHandle StatManager;
	GetWorld()->GetTimerManager().SetTimer(StatManager, [&]()
		{
			if (!isDragging) {
				StaticMeshComponent->GetBodyInstance()->bLockXTranslation = true;
				StaticMeshComponent->GetBodyInstance()->bLockYTranslation = true;
				StaticMeshComponent->GetBodyInstance()->bLockZTranslation = true;
				StaticMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
				StaticMeshComponent->SetMobility(EComponentMobility::Static);
			}
		}, 1.3f, false);

	FVector Min, Max;
	StaticMeshComponent->GetLocalBounds(Min, Max);

	NewBoxSize = (Max - Min) / 2;
	NewBoxSize.Z = 0;

}


void APlaceable::OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	isDragging = true;
	StaticMeshComponent->GetBodyInstance()->bLockXTranslation = false;
	StaticMeshComponent->GetBodyInstance()->bLockYTranslation = false;
	StaticMeshComponent->GetBodyInstance()->bLockZTranslation = false;
	StaticMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
}

void APlaceable::LockPosition(bool block)
{
	if (StaticMeshComponent->GetBodyInstance()->bLockXTranslation) {
		StaticMeshComponent->GetBodyInstance()->bLockXTranslation = false;
		StaticMeshComponent->GetBodyInstance()->bLockYTranslation = false;
		StaticMeshComponent->GetBodyInstance()->bLockZTranslation = false;
		StaticMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
		StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	}
	else {
		StaticMeshComponent->GetBodyInstance()->bLockXTranslation = true;
		StaticMeshComponent->GetBodyInstance()->bLockYTranslation = true;
		StaticMeshComponent->GetBodyInstance()->bLockZTranslation = true;
		StaticMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
		StaticMeshComponent->SetMobility(EComponentMobility::Static);
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

		FVector Start = GetActorLocation();
		FVector End = ((GetActorUpVector() * -100.f) + Start);

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		TArray<FHitResult> HitResult;

		bool BoxHit = UKismetSystemLibrary::BoxTraceMulti(GetWorld(), Start, End,
			NewBoxSize,
			GetActorRotation(), UEngineTypes::ConvertToTraceType(ECC_Pawn),
			false, ActorsToIgnore, EDrawDebugTrace::None, HitResult,
			true, FLinearColor::Red, FLinearColor::Green, 0.1f
		);

		if (BoxHit) {
			for (auto& Building : HitResult)
			{
				APlaceable* UnderHit = Cast<APlaceable>(Building.GetActor());
				if (UnderHit) {
					this->SetActorLocation(oldPos);
				}
				
			}
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

	FTimerHandle StatManager;
	GetWorld()->GetTimerManager().SetTimer(StatManager, [&]()
		{
			if (!isDragging) {
				StaticMeshComponent->GetBodyInstance()->bLockXTranslation = true;
				StaticMeshComponent->GetBodyInstance()->bLockYTranslation = true;
				StaticMeshComponent->GetBodyInstance()->bLockZTranslation = true;
				StaticMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
				StaticMeshComponent->SetMobility(EComponentMobility::Static);
			}
		}, 1.3f, false);
}

void APlaceable::DestroyBuildingActor()
{
	Destroy();
}
