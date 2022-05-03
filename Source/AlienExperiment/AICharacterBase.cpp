// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Resturant.h"
#include "AIControllerBase.h"
#include "Hotel.h"

// Sets default values
AAICharacterBase::AAICharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NotHungry = 100;
	NotSleepy = 100;

}

// Called when the game starts or when spawned
void AAICharacterBase::BeginPlay()
{
	Super::BeginPlay();
	GettingHungry();
	GettingSleepy();
	//MoveToResturant();
}

void AAICharacterBase::GettingHungry()
{
	FTimerHandle HungryManager;
	GetWorld()->GetTimerManager().SetTimer(HungryManager, this, &AAICharacterBase::ChangeNotHungryAttr, 1.0f, true);
}

void AAICharacterBase::GettingSleepy()
{
	FTimerHandle SleepyManager;
	GetWorld()->GetTimerManager().SetTimer(SleepyManager, this, &AAICharacterBase::ChangeNotSleepyAttr, 1.0f, true);
}

void AAICharacterBase::ChangeNotHungryAttr()
{
	if (NotHungry > 0)
		NotHungry -= 1;

	if (NotHungry < 90 && !GoingToHotel) {
		MoveToResturant();
		GoingToResturant = true;
	}

	if (NotHungry > 90)
	{
		GoingToResturant = false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Not Hungry: %d"), NotHungry);
}

void AAICharacterBase::ChangeNotSleepyAttr()
{
	if (NotSleepy > 0)
		NotSleepy -= 1;

	if (NotSleepy < 95 && !GoingToResturant)
	{
		GoingToHotel = true;
		MoveToHotel();
	}

	if (NotSleepy > 95)
		GoingToHotel = false;

	UE_LOG(LogTemp, Warning, TEXT("Not Sleepy: %d"), NotSleepy);
}


// Called to bind functionality to input
void AAICharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacterBase::MoveToResturant()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AResturant::StaticClass(), Resturants);

	AAIControllerBase* AI = Cast<AAIControllerBase>(GetController());

	if (!AI)
		return;

	for (AActor* Resturant : Resturants)
	{
		AResturant* Rest = Cast<AResturant>(Resturant);

		if (Rest)
		{
			AI->MoveTo(Rest->GetActorLocation());
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Moving"));
		}
	}
}

void AAICharacterBase::MoveToHotel()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHotel::StaticClass(), Hotels);
	UE_LOG(LogTemp, Warning, TEXT("Hotels: %d"), Hotels.Num());

	AAIControllerBase* AI = Cast<AAIControllerBase>(GetController());

	if (!AI)
		return;

	for (AActor* Hotel : Hotels)
	{
		AHotel* Hot = Cast<AHotel>(Hotel);

		if (Hot)
		{
			AI->MoveTo(Hot->GetActorLocation());
		}
	}
}
