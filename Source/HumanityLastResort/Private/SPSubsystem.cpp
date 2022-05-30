// Fill out your copyright notice in the Description page of Project Settings.


#include "SPSubsystem.h"
#include "PlacementInterface.h"
#include "BuildingsActors.h"
#include "RunTime\Engine\Classes\Kismet\GameplayStatics.h"


void USPSubsystem::OnLeftMouseRelease()
{
	TArray<AActor*> actorPtrs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildingsActors::StaticClass(), actorPtrs);
	if (actorPtrs.Num() != 0) {
		for (AActor* actor : actorPtrs) {

			IPlacementInterface* ReactingObject = Cast<IPlacementInterface>(actor);

			if(ReactingObject) {
				ReactingObject->MouseRelease();

			}
		}
	}
}