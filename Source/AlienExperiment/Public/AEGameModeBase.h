// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AEGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ALIENEXPERIMENT_API AAEGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		TArray<TSubclassOf<class ABuildingsActors>> building;

};
