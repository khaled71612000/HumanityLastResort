// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Components/SphereComponent.h"
#include "AI/Alien.h"
#include "Economy/EconomySubsystem.h"
#include "SelectionSubsystem.h"



ABuilding::ABuilding() 
{
	CurOccupants = 0;

	BuildingCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RootCollision"));
	BuildingCollision->SetupAttachment(RootComponent);
	BuildingCollision->SetSphereRadius(200.f);
	BuildingCollision->SetHiddenInGame(false);
	BuildingCollision->OnComponentBeginOverlap.AddDynamic(this, &ABuilding::OnOverlap);
	BuildingCollision->OnComponentEndOverlap.AddDynamic(this, &ABuilding::OnOverlapEnd);
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	EconomySubsystem = GetWorld()->GetSubsystem<UEconomySubsystem>();
	
	SelectionSubSystem = GetWorld()->GetSubsystem<USelectionSubsystem>();
	SelectionSubSystem->RegisterSelectionHandler(Cast<IISelectionHandler>(this));
}

void ABuilding::AddProfit()
{
	EconomySubsystem->AddCash(Profit);
}

void ABuilding::SubtractLoss()
{
	EconomySubsystem->SubtractCash(Loss);
}


ABuilding* ABuilding::Selected(const FHitResult& selectionInfoRay)
{
	UE_LOG(LogTemp, Error, TEXT("SELECTED")); 
	return this;
}

void ABuilding::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void ABuilding::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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