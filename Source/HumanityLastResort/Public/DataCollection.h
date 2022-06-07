// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "DataCollection.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FBGBuildBank : public FTableRowBase
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText TokenName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf <class APlaceable> BuildingsActorsClassREFF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PriceBuilding = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSlateBrush Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PlaceableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* Mesh;
};
UCLASS()
class HUMANITYLASTRESORT_API UDataCollection : public UObject
{
	GENERATED_BODY()
	
};
