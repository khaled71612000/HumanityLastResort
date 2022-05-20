// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HungerSatisfactionTask.h"
#include "Resturant.h"
#include "Kismet/GameplayStatics.h"
#include "AI/AlienAIController.h"
#include "AI/Alien.h"
#include "AI/NeedComponent.h"

void UHungerSatisfactionTask::Satisfy(AAlien* Alien, UNeedComponent* Need)
{
	CurrentAlien = Alien;
	Hunger = Need;
	
	AResturant* Resturant = GetResturant();
	MoveToResturant(Resturant);

	//UE_LOG(LogTemp, Warning, TEXT("Hungry"));
}

AResturant* UHungerSatisfactionTask::GetResturant()
{
	TArray<AActor*> Resturants;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AResturant::StaticClass(), Resturants);

	int32 NumOfResturants = Resturants.Num();
	int32 ShuffleTurns = NumOfResturants/2;
	int32 Index1;
	int32 Index2;
	AActor* Temp;

	if (NumOfResturants > 1)
	{
		while (ShuffleTurns--)
		{
			Index1 = FMath::RandRange(0, NumOfResturants - 1);
			Index2 = FMath::RandRange(0, NumOfResturants - 1);
			Temp = Resturants[Index1];
			Resturants[Index1] = Resturants[Index2];
			Resturants[Index2] = Temp;
		}
	}
	
	for (AActor* Resturant : Resturants)
	{
		AResturant* Rest = Cast<AResturant>(Resturant);
		if (Rest->CurOccupant < Rest->Capacity)
			return Rest;

	}

	return nullptr;
}

void UHungerSatisfactionTask::MoveToResturant(AResturant* Resturant)
{
	if (Resturant)
	{
		AAlienAIController* AI = Cast<AAlienAIController>(CurrentAlien->GetController());
		if (AI)
		{
			Resturant->CurOccupant++;
			CurrentAlien->AlienState = Assigned;
			AI->MoveToLocation(Resturant->GetActorLocation());

		}
	}
}

void UHungerSatisfactionTask::Wait()
{
	CurrentAlien->AlienState = Waiting;
	EatingTime = Hunger->TaskTime;
	if (GetWorld()->GetTimerManager().IsTimerPaused(EatingTimeManager))
		GetWorld()->GetTimerManager().UnPauseTimer(EatingTimeManager);
	else
		GetWorld()->GetTimerManager().SetTimer(EatingTimeManager, this, &UHungerSatisfactionTask::Eat, 1.f, true);
		
}

void UHungerSatisfactionTask::Eat()
{
	EatingTime--;

	if (EatingTime == 0)
	{
		Hunger->CurValue = Hunger->MaxCapacity;
		CurrentAlien->AlienState = Idle;
		GetWorld()->GetTimerManager().PauseTimer(EatingTimeManager);
	}

}

