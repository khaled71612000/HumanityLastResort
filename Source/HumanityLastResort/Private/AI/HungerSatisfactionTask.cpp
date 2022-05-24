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
	TaskComponent = Need;
	
	AResturant* Resturant = GetResturant();
	if (Resturant)
		MoveToResturant(Resturant);
	else
		Alien->AlienState = Idle;

	//UE_LOG(LogTemp, Warning, TEXT("Hungry"));
}

AResturant* UHungerSatisfactionTask::GetResturant()
{
	TArray<AActor*> Resturants;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AResturant::StaticClass(), Resturants);

	

	ShuffleBuildings(Resturants);

	for (AActor* Resturant : Resturants)
	{
		AResturant* Rest = Cast<AResturant>(Resturant);
		UE_LOG(LogTemp, Warning, TEXT("Rest: %d"), Rest->CurOccupants);

		if (Rest)
		{
			if (Rest->CurOccupants < Rest->Capacity)
				return Rest;
		}
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
			Resturant->CurOccupants++;
			CurrentAlien->AlienState = Assigned;
			AI->CurBuilding = Resturant;
			AI->MoveToLocation(Resturant->GetActorLocation());

		}
	}
}


