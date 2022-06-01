//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "AI/Needs/Resting.h"
//#include "AI/AlienAIController.h"
//#include "AI/Alien.h"
//#include "AI/NeedComponent.h"
//#include "Kismet/GameplayStatics.h"
//#include "Buildings/Hotel.h"
//
//void UResting::Satisfy(class AAlien* Alien, class UNeedComponent* Need)
//{
//	CurrentAlien = Alien;
//	TaskComponent = Need;
//
//	AHotel* Hotel = GetHotel();
//	if (Hotel)
//		MoveToHotel(Hotel);
//	else
//		Alien->AlienState = Idle;
//}
//
//AHotel* UResting::GetHotel()
//{
//	TArray<AActor*> Hotels;
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHotel::StaticClass(), Hotels);
//	
//	ShuffleBuildings(Hotels);
//	
//	for (AActor* Hotel : Hotels)
//	{
//		AHotel* Hot = Cast<AHotel>(Hotel);
//		if (Hot)
//		{
//			if (Hot->CurOccupants < Hot->Capacity)
//				return Hot;
//		}
//	}
//	return nullptr;
//}
//
//void UResting::MoveToHotel(AHotel* Hotel)
//{
//	if (Hotel)
//	{
//		AAlienAIController* AI = Cast<AAlienAIController>(CurrentAlien->GetController());
//		if (AI)
//		{
//			Hotel->CurOccupants++;
//			UE_LOG(LogTemp, Warning, TEXT("Rest: %d"), Hotel->CurOccupants);
//			CurrentAlien->AlienState = Assigned;
//			AI->CurBuilding = Hotel;
//			AI->MoveToLocation(Hotel->GetActorLocation());
//		}
//	}
//}
