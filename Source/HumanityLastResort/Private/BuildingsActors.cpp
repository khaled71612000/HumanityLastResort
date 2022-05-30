// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingsActors.h"
#include "CameraPawn.h"
#include "Kismet\KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "CellActor.h"
#include "Math/UnrealMathUtility.h"
#include "RunTime\Engine\Classes\Kismet\GameplayStatics.h"
#include "Economy/EconomySubsystem.h"
#include "Components/SphereComponent.h"
#include "AI/Alien.h"


ABuildingsActors::ABuildingsActors()
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

	CurOccupants = 0;

	BuildingCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RootCollision"));

	BuildingCollision->SetupAttachment(RootComponent);
	BuildingCollision->SetSphereRadius(200.f);
	BuildingCollision->SetHiddenInGame(false);

	BuildingCollision->OnComponentBeginOverlap.AddDynamic(this, &ABuildingsActors::OnOverlap);
	BuildingCollision->OnComponentEndOverlap.AddDynamic(this, &ABuildingsActors::OnOverlapEnd);

}

void ABuildingsActors::BeginPlay()
{
	Super::BeginPlay();
	EconomySubsystem = GetWorld()->GetSubsystem<UEconomySubsystem>();

	StaticMeshComponent->OnClicked.AddDynamic(this, &ABuildingsActors::OnClicked);
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


void ABuildingsActors::OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	isDragging = true;
	StaticMeshComponent->GetBodyInstance()->bLockXTranslation = false;
	StaticMeshComponent->GetBodyInstance()->bLockYTranslation = false;
	StaticMeshComponent->GetBodyInstance()->bLockZTranslation = false;
	StaticMeshComponent->GetBodyInstance()->SetDOFLock(EDOFMode::Default);
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
}

void ABuildingsActors::LockPosition(bool block)
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


void ABuildingsActors::ResetRotation()
{
	SetActorRotation(FRotator::ZeroRotator);
}


void ABuildingsActors::MouseMove(FVector position)
{

	if (isDragging)
	{
		ClearFloor();
		FVector origin, boxExtent;
		GetActorBounds(false, origin, boxExtent);
		boxExtent.Z = 1.f;

		if (isOneCell) {
			position.X += 195;
			position.Y += 195;
			this->SetActorLocation(position);
		}
		else {
			this->SetActorLocation(position + NewBoxSize);
		}
		this->SetActorLocation(position);

		 MyPawn = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<ACameraPawn>();
		   if(MyPawn)
		   MyPawn->SelectedToken = this;
		   
		   FVector Start = GetActorLocation();
		   FVector End = ((GetActorUpVector() * 50.f) + Start);

		   TArray<AActor*> ActorsToIgnore;
		   ActorsToIgnore.Add(this);
		   FHitResult HitResult;

		   bool BoxHit = UKismetSystemLibrary::BoxTraceSingle(GetWorld(), Start, End,
			   NewBoxSize ,
			   GetActorRotation(), UEngineTypes::ConvertToTraceType(ECC_Pawn),
			   false, ActorsToIgnore, EDrawDebugTrace::None, HitResult,
			   true, FLinearColor::Red, FLinearColor::Green, 0.1f
		   );

		if (BoxHit) {
			ABuildingsActors* UnderHit = Cast<ABuildingsActors>(HitResult.GetActor());
			if (UnderHit) {
				this->SetActorLocation(oldPos);
			}
		}
		
	}
}

void ABuildingsActors::ClearFloor()
{
	FVector Start = GetActorLocation() ;
	FVector End = ((GetActorUpVector() * 60.f) + Start);

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
		UE_LOG(LogTemp, Error, TEXT("NPC FOUND"));
		for (auto& NPC : HitArray)
		{
			AAlien* NPCHit = Cast<AAlien>(NPC.GetActor());
			if (NPCHit) {
				NPCHit->SetActorLocation(FVector(200,7800,190), true);
			}
		}
	}
}



void ABuildingsActors::MouseRelease()
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

void ABuildingsActors::DestroyBuildingActor()
{
	Destroy();
}

void ABuildingsActors::AddProfit()
{
	EconomySubsystem->AddCash(Profit);
}

void ABuildingsActors::SubtractLoss()
{
	EconomySubsystem->SubtractCash(Loss);
}

void ABuildingsActors::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		AAlien* Alien = Cast<AAlien>(OtherActor);
		
		if (Alien)
		{
			Alien->AlienState = Arrived;			
		}
	}
}

void ABuildingsActors::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		AAlien* Alien = Cast<AAlien>(OtherActor);
		
		if (Alien)
		{
			CurOccupants--;
		}
	}
}
