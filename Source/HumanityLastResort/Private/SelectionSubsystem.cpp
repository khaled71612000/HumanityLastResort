// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionSubsystem.h"

void USelectionSubsystem::RegisterSelectionHandler(IISelectionHandler* handler)
{
	Handlers.Add(handler);
}

ABuilding* USelectionSubsystem::TrySelect(const FHitResult& selectionInfoRay)
{
	for (IISelectionHandler* handler : Handlers)
	{
		ABuilding* selection = handler->Selected(selectionInfoRay);
		if (selection)
		{
			return selection;
		}
	}
		return nullptr;
}
