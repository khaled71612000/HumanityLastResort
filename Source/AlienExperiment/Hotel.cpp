// Fill out your copyright notice in the Description page of Project Settings.


#include "Hotel.h"
#include "Components/SphereComponent.h"
#include "AICharacterBase.h"

AHotel::AHotel(const FObjectInitializer& objectInitializer)
{
	Capacity = 2;
	Residents = 0;

	HotelCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RootCollision"));

	HotelCollision->SetSphereRadius(600.f);
	HotelCollision->SetHiddenInGame(false);

	RootComponent = HotelCollision;

	HotelCollision->OnComponentBeginOverlap.AddDynamic(this, &AHotel::OnOverlap);
	HotelCollision->OnComponentEndOverlap.AddDynamic(this, &AHotel::OnOverlapEnd);
}

void AHotel::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		AAICharacterBase* Chr = Cast<AAICharacterBase>(OtherActor);
		if (Chr)
		{
			if (Chr->SleepyManager.IsValid())
			{
				GetWorld()->GetTimerManager().PauseTimer(Chr->SleepyManager);
			}

			Chr->NotSleepy = 100;
			Chr->isSleepy = false;
			Chr->TaskState = Idle;
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Begin Overlap"));
			
		}
	}

}

void AHotel::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Residents -= 1;
	AAICharacterBase* Chr = Cast<AAICharacterBase>(OtherActor);

	if (Chr && Chr->SleepyManager.IsValid())
	{
		GetWorld()->GetTimerManager().UnPauseTimer(Chr->SleepyManager);
	}
}
