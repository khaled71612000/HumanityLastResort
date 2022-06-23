// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "ISelectionHandler.h"
#include "Subsystems/WorldSubsystem.h"
#include "SelectionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API USelectionSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
		TArray<IISelectionHandler*> Handlers;
public:
		void RegisterSelectionHandler( IISelectionHandler* handler);
		void RemoveSelectionHandler(IISelectionHandler* handler);
		APlaceable* TrySelect(const FHitResult& selectionInfoRay);
		void DeSelect(const FHitResult& selectionInfoRay);

};
