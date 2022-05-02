// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <CellActor.h>
#include "GameFramework/Actor.h"
#include "MapActor.generated.h"

UCLASS()
class ALIENEXPERIMENT_API AMapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapActor();

	UFUNCTION(BlueprintCallable)
		void BuildMap(const FVector CenterLocation, const int X, const int Y);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D MapSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> MapTiles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<ACellActor> CellClass;

};
