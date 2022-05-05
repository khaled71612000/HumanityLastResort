// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingsActors.generated.h"




UCLASS()
class ALIENEXPERIMENT_API ABuildingsActors : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildingsActors();
	UFUNCTION(BlueprintCallable, Category = "Functions")
		void LockPosition(bool block);
	UFUNCTION(BlueprintCallable, Category = "Functions")
		void DestroyBuildingActor();
	void MouseMove(FVector position);
	void MouseRelease( );

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "BuildTransform")
		void ResetRotation();

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	FText TokenName;

	UFUNCTION()
	void OnClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);
	bool isDragging = false;
	class ACameraPawn* MyPawn;
};
