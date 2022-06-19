// Fill out your copyright notice in the Description page of Project Settings.


#include "SPSubsystem.h"
#include "PlacementInterface.h"
#include "Placeable.h"
#include "RunTime\Engine\Classes\Kismet\GameplayStatics.h"


void USPSubsystem::OnLeftMouseRelease()
{
	TArray<AActor*> actorPtrs;

	UGameplayStatics::GetAllActorsWithInterface(GetWorld(),
		UPlacementInterface::StaticClass(), actorPtrs);

	if (actorPtrs.Num() != 0) {
		for (AActor* actor : actorPtrs) {

			IPlacementInterface* ReactingObject = Cast<IPlacementInterface>(actor);

			if(ReactingObject) {
				ReactingObject->MouseRelease();
			}
		}
	}
}