// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RestSatisfactionTask.h"
#include "Hotel.h"
#include "AI/AlienAIController.h"
#include "AI/Alien.h"
#include "AI/NeedComponent.h"
#include "Kismet/GameplayStatics.h"


void URestSatisfactionTask::Satisfy(AAlien* Alien, UNeedComponent* Need)
{
	CurrentAlien = Alien;
	TaskComponent = Need;

	AHotel* Hotel = GetHotel();
	if (Hotel)
		MoveToHotel(Hotel);
}

AHotel* URestSatisfactionTask::GetHotel()
{
	TArray<AActor*> Hotels;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHotel::StaticClass(), Hotels);

	ShuffleBuildings(Hotels);

	for (AActor* Hotel : Hotels)
	{
		AHotel* Hot = Cast<AHotel>(Hotel);
		if (Hot)
		{
			if (Hot->CurOccupants < Hot->Capacity)
				return Hot;
		}
	}
	return nullptr;
}


void URestSatisfactionTask::MoveToHotel(AHotel* Hotel)
{
	if (Hotel)
	{
		AAlienAIController* AI = Cast<AAlienAIController>(CurrentAlien->GetController());
		if (AI)
		{
			Hotel->CurOccupants++;
			CurrentAlien->AlienState = Assigned;
			AI->MoveToLocation(Hotel->GetActorLocation());
		}
	}
}
