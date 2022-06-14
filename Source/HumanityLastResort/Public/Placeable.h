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
	UFUNCTION(BlueprintCallable, Category = "Functions")
		void LockPosition(bool block);
	UFUNCTION(BlueprintCallable, Category = "Functions")
		void DestroyBuildingActor();

	virtual void MouseMove(FVector position) override;
	virtual void MouseRelease() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
		FVector RespawnLoc = FVector(200, 7800, 190);

	void ClearFloor();
	FVector NewBoxSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cells")
		FText NameView;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* StaticMeshComponent;

protected:
	APlaceable();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "BuildTransform")
		void ResetRotation();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* SceneComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
		FText TokenName;

	UFUNCTION()
		void OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	bool isDragging = false;
	class ACameraPawn* MyPawn;
	FVector oldPos;
	class UBuildingSubsystem* BuildingSubsystem;
	class URoadSubsystem* RoadSubsystem;
	class USelectionSubsystem* SelectionSubSystem;

};
