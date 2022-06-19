// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISelectionHandler.h"
#include "Placeable.h"
#include "Building.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum BuildingType
{
	Hotel UMETA(DisplayName = "Hotel"),
	Resturant UMETA(DisplayName = "Resturant"),
	Casino UMETA(DisplayName = "Casino"),
	Club UMETA(DisplayName = "Club"),
	JuiceShop UMETA(DisplayName = "JuiceShop"),
	CandyShop UMETA(DisplayName = "CandyShop"),
	KidsArea UMETA(DisplayName = "KidsArea"),
};

UCLASS()
class HUMANITYLASTRESORT_API ABuilding : public APlaceable, public IISelectionHandler
{
	GENERATED_BODY()
public:

	void AddProfit();
	void SubtractLoss();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	TEnumAsByte<BuildingType> BuildingType;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	int32 Capacity;
	UPROPERTY(Transient)
	int32 CurOccupants;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	int32 Profit;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	int32 Loss;
	UPROPERTY()
	class UEconomySubsystem* EconomySubsystem;
	class USelectionSubsystem* SelectionSubSystem;
	 UWorld*  world;

	virtual APlaceable* Selected(const FHitResult& selectionInfoRay) override;
	virtual void HightLight() override;
	virtual void DeHighLight() override;

protected:
	ABuilding();
	virtual void BeginPlay() override;

};
