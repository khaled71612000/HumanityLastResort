// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISelectionHandler.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UISelectionHandler : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HUMANITYLASTRESORT_API IISelectionHandler
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class APlaceable* Selected(const FHitResult& selectionInfoRay) = 0;
	virtual void HightLight() = 0;
	virtual void DeHighLight() = 0;
};
