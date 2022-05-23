// Fill out your copyright notice in the Description page of Project Settings.


#include "Resturant.h"
#include "Components/SphereComponent.h"
#include "AICharacterBase.h"

AResturant::AResturant(const FObjectInitializer& objectInitializer)
{
	RestCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RootCollision"));

	RestCollision->SetSphereRadius(200.f);
	RestCollision->SetHiddenInGame(false);

	RootComponent = RestCollision;

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
			if (Chr->HungryManager.IsValid())
			{
				GetWorld()->GetTimerManager().PauseTimer(Chr->HungryManager);
			}

			Chr->NotHungry = 100;
			Chr->isHungry = false;
			Chr->TaskState = Idle;
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Begin Overlap"));
		}
	}

}

void AResturant::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Residents -= 1;
	AAICharacterBase* Chr = Cast<AAICharacterBase>(OtherActor);

	if (Chr && Chr->HungryManager.IsValid())
	{
		GetWorld()->GetTimerManager().UnPauseTimer(Chr->HungryManager);
	}
}
