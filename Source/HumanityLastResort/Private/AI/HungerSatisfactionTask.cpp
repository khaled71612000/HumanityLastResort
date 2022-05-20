// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HungerSatisfactionTask.h"
#include "Resturant.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "AI/Alien.h"

void UHungerSatisfactionTask::Satisfy(AAlien* Alien)
{
	TArray<AActor*> Resturants;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AResturant::StaticClass(), Resturants);

	for (AActor* Resturant : Resturants)
	{
		AResturant* Rest = Cast<AResturant>(Resturant);

		if (Rest)
		{
			if (Rest->CurOccupant < Rest->Capacity)
			{
				Rest->CurOccupant++;
				AAIController* AI = Cast<AAIController>(Alien->GetController());
				if (AI)
					AI->MoveToLocation(Rest->GetActorLocation());
			}
		}


	}

	UE_LOG(LogTemp, Warning, TEXT("Hungry"));
}
