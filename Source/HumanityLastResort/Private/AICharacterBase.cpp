// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacterBase.h"
#include "Resturant.h"
#include "Hotel.h"
#include "Kismet/GameplayStatics.h"
#include "AIControllerBase.h"

// Sets default values
AAICharacterBase::AAICharacterBase()
{
	/*ConstructorHelpers::FObjectFinder<USkeletalMesh> SSMeshRef(TEXT("SkeletalMesh'/Engine/Tutorial/SubEditors/TutorialAssets/Character/TutorialTPP.TutorialTPP'"));
	if (SSMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SSMeshRef.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}*/

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
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

	//UE_LOG(LogTemp, Warning, TEXT("Not Sleepy: %d"), NotSleepy);
}


// Called to bind functionality to input
void AAICharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacterBase::MoveToResturant()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AResturant::StaticClass(), Resturants);

	AAIController* AI = Cast<AAIController>(GetController());
	if (!AI)
		return;

	for (AActor* Resturant : Resturants)
	{
		AResturant* Rest = Cast<AResturant>(Resturant);

		if (Rest)
		{
			AI->MoveToLocation(Rest->GetActorLocation() , 250.f);
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Moving"));
		}
	}
}

void AAICharacterBase::MoveToHotel()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHotel::StaticClass(), Hotels);
	//UE_LOG(LogTemp, Warning, TEXT("Hotels: %d"), Hotels.Num());

	AAIController* AI = Cast<AAIController>(GetController());

	if (!AI)
		return;

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Move?"));

	for (AActor* Hotel : Hotels)
	{
		AHotel* Hot = Cast<AHotel>(Hotel);

		if (Hot)
		{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Moving"));
			AI->MoveToLocation(Hot->GetActorLocation() , 250.f);
		}
	}
}
