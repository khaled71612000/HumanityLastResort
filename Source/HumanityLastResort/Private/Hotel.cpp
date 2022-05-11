// Fill out your copyright notice in the Description page of Project Settings.


#include "Hotel.h"
#include "Components/SphereComponent.h"
#include "AICharacterBase.h"

AHotel::AHotel(const FObjectInitializer& objectInitializer)
{
	HotelCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RootCollision"));

	HotelCollision->SetupAttachment(RootComponent);

	HotelCollision->SetSphereRadius(200.f);
	HotelCollision->SetHiddenInGame(false);

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
			Chr->NotSleepy = 100;
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Begin Overlap"));
			
		}
	}
}

void AHotel::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("End Overlap"));
	if (OtherActor && OtherActor != this)
	{
		AAICharacterBase* Chr = Cast<AAICharacterBase>(OtherActor);

		if (Chr)
		{
			Chr->NotSleepy = 100;
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Begin Overlap"));
		}
	}
}
