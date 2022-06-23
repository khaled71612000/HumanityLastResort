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
	FVector OriginSklet, HalfBoxSklet;
	float sphereRad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
		FVector RespawnLoc = FVector(200, 5780, 20);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cells")
		FText NameView;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USkeletalMeshComponent* SkeletalMeshComponent;

	void ClearFloor();
	
	UFUNCTION(BlueprintCallable, Category = "Functions")
		void LockPosition(bool block);
	UFUNCTION(BlueprintCallable, Category = "Functions")
		void DestroyBuildingActor();
	 UWorld*  world;
protected:
	APlaceable();

	bool isDragging = false;
	FVector oldPos;


	UPROPERTY()
	class ACameraPawn* MyPawn;
	UPROPERTY()
		class URoadSubsystem* RoadSubsystem;
	UPROPERTY()
		class USelectionSubsystem* SelectionSubSystem;
	UPROPERTY()
	class UBuildingSubsystem* BuildingSubsystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* SceneComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
		FText TokenName;

	UFUNCTION()
		void OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);
	UFUNCTION(BlueprintCallable, Category = "BuildTransform")
		void ResetRotation();

	virtual void MouseMove(FVector position) override;
	virtual void MouseRelease() override;
	virtual void BeginPlay() override;


};
