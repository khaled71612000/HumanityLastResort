// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingsActors.h"
#include "CameraPawn.h"
#include "AICharacterBase.h"
#include "Kismet\KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "CellActor.h"
#include "Math/UnrealMathUtility.h"
#include "RunTime\Engine\Classes\Kismet\GameplayStatics.h"

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

	//StaticMeshComponent->SetRelativeScale3D(FVector(0.75f, 0.75f, 1.5f));
	
}

void ABuildingsActors::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void ABuildingsActors::OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	//UE_LOG(LogTemp, Warning, TEXT("HERE Clicked %d"));
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
		//UE_LOG(LogTemp, Warning, TEXT("Moving"));
		this->SetActorLocation(position);
	    MyPawn = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<ACameraPawn>();
		
		if(MyPawn)
		MyPawn->SelectedToken = this;

		FVector Start = GetActorLocation();
		FVector End = ((GetActorUpVector() * -1 * 10000.f) + Start);

		FVector origin, boxExtent;
		GetActorBounds(false , origin , boxExtent);
		boxExtent.Z = 1.f;

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		FHitResult HitArray;

		bool BoxHit = UKismetSystemLibrary::BoxTraceSingle(GetWorld(), Start, End, boxExtent,
			FRotator(0, 0, 0), UEngineTypes::ConvertToTraceType(ECC_Pawn),
			false, ActorsToIgnore, EDrawDebugTrace::None, HitArray,
			true, FLinearColor::Red, FLinearColor::Green, 0.1f
		);

		if (BoxHit) {
			//UE_LOG(LogTemp, Error, TEXT("Colliding"))
			ABuildingsActors* UnderHit = Cast<ABuildingsActors>(HitArray.GetActor());
			//DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 0.1f);
			if (UnderHit) {
				//GEngine->AddOnScreenDebugMessage(-1, 1 ,FColor::Yellow, FString::Printf(TEXT("HERE %s"), *Hit.GetActor()->GetName()));
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
		FRotator(0, 0, 0), UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitArray,
		true, FLinearColor::Green, FLinearColor::Yellow, 0.1f
	);

	if (Hiting) {
		UE_LOG(LogTemp, Error, TEXT("NPC FOUND"));
		for (auto& NPC : HitArray)
		{
			AAICharacterBase* NPCHit = Cast<AAICharacterBase>(NPC.GetActor());
			if (NPCHit) {
				NPCHit->SetActorLocation(FVector(200,7800,190), true);
			}
		}
	}
}



void ABuildingsActors::MouseRelease()
{
	//UE_LOG(LogTemp, Warning, TEXT("HERE release %d"));
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
