// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlacementInterface.h"
#include "GameFramework/Actor.h"
#include "Placeable.generated.h"

UCLASS()
class HUMANITYLASTRESORT_API APlaceable : public AActor, public IPlacementInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceable();
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 Capacity;
	UPROPERTY(Transient)
		int32 CurOccupants;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 Profit;
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
		int32 Loss;

public:
	UFUNCTION(BlueprintCallable, Category = "Functions")
		void LockPosition(bool block);
	UFUNCTION(BlueprintCallable, Category = "Functions")
		void DestroyBuildingActor();

	virtual void MouseMove(FVector position) override;
	virtual void MouseRelease() override;

	void ClearFloor();
	FVector NewBoxSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cells")
		bool isOneCell = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cells")
		FText NameView;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "BuildTransform")
		void ResetRotation();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
		FText TokenName;

	UFUNCTION()
		void OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);
	bool isDragging = false;
	class ACameraPawn* MyPawn;
	FVector oldPos;


};
