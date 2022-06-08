// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "AEGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API AAEGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AAEGameModeBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<class APlaceable>> building;
	

};
