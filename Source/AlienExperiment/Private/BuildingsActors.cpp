// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingsActors.h"
#include "CameraPawn.h"
#include "DrawDebugHelpers.h"
#include "RunTime\Engine\Classes\Kismet\GameplayStatics.h"

ABuildingsActors::ABuildingsActors()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->bIgnoreRadialForce = true;
	StaticMeshComponent->bIgnoreRadialImpulse = true;
	StaticMeshComponent->SetLinearDamping(2.f);
	StaticMeshComponent->SetAngularDamping(2.f);

	//StaticMeshComponent->SetRelativeScale3D(FVector(0.75f, 0.75f, 1.5f));


}

void ABuildingsActors::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMeshComponent->OnClicked.AddDynamic(this, &ABuildingsActors::OnClicked);
}

void ABuildingsActors::OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	//UE_LOG(LogTemp, Warning, TEXT("HERE Clicked %d"));
	isDragging = true;
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
		//UE_LOG(LogTemp, Warning, TEXT("Moving"));
		this->SetActorLocation(position);
	    MyPawn = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<ACameraPawn>();
		if(MyPawn)
		MyPawn->SelectedToken = this;

		FVector Start = GetActorLocation();
		FVector End = ((GetActorUpVector() * -1 * 10000.f) + Start);
		FHitResult Hit;
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
		if (bHit) {
			ABuildingsActors* UnderHit = Cast<ABuildingsActors>(Hit.GetActor());
			DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 0.1f);
			if (UnderHit) {
				GEngine->AddOnScreenDebugMessage(-1, 1 ,FColor::Yellow, FString::Printf(TEXT("HERE %s"), *Hit.GetActor()->GetName()));
				this->SetActorLocation(FVector::ZeroVector);
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
}

void ABuildingsActors::DestroyBuildingActor()
{
	Destroy();
}
