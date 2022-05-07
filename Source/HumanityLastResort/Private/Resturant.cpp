// Fill out your copyright notice in the Description page of Project Settings.


#include "Resturant.h"
#include "Components/SphereComponent.h"
#include "AICharacterBase.h"

AResturant::AResturant(const FObjectInitializer& objectInitializer)
{
	RestCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RootCollision"));

	RestCollision->SetupAttachment(RootComponent);

	RestCollision->SetSphereRadius(200.f);
	RestCollision->SetHiddenInGame(false);


	RestCollision->OnComponentBeginOverlap.AddDynamic(this, &AResturant::OnOverlap);
	RestCollision->OnComponentEndOverlap.AddDynamic(this, &AResturant::OnOverlapEnd);

}


void AResturant::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		AAICharacterBase* Chr = Cast<AAICharacterBase>(OtherActor);

		if (Chr)
		{
			Chr->NotHungry = 100;
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Begin Overlap"));
		}
	}

}

void AResturant::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("End Overlap"));
	if (OtherActor && OtherActor != this)
	{
		AAICharacterBase* Chr = Cast<AAICharacterBase>(OtherActor);

		if (Chr)
		{
			Chr->NotHungry = 100;
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Begin Overlap"));
		}
	}
}
