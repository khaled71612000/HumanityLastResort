// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionSubsystem.h"

void USelectionSubsystem::RegisterSelectionHandler(IISelectionHandler* handler)
{
	Handlers.Add(handler);
}
void USelectionSubsystem::RemoveSelectionHandler(IISelectionHandler* handler)
{
	Handlers.Remove(handler);
}
APlaceable* USelectionSubsystem::TrySelect(const FHitResult& selectionInfoRay)
{
	for (IISelectionHandler* handler : Handlers)
	{
		APlaceable* selection = handler->Selected(selectionInfoRay);
		if (selection == selectionInfoRay.GetActor())
		{
			handler->HightLight();
			return selection;
		}
	}
		return nullptr;
}
void USelectionSubsystem::DeSelect(const FHitResult& selectionInfoRay)
{
	for (IISelectionHandler* handler : Handlers)
	{
		APlaceable* selection = handler->Selected(selectionInfoRay);
		if (selection == selectionInfoRay.GetActor())
		{
			handler->DeHighLight();
		}
	}

}
