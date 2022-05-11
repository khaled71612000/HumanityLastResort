// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EconomySubsystem.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		TArray<TSubclassOf<class ABuildingsActors>> building;
	
	//UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	//UGameInstanceSubsystem* EconomySubsystem = GameInstance->GetSubsystem<UGameInstanceSubsystem>();
	UGameInstance* GameInstanceRef = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UEconomySubsystem* EconomySubsystem;

};
