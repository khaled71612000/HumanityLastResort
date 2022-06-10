// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "StructureDragDrop.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API UStructureDragDrop : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
		UPROPERTY(EditAnywhere, BlueprintType, BlueprintReadWrite, Category="Stats")
		int x;
};
