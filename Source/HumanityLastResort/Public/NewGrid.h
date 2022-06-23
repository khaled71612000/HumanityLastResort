// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NewGrid.generated.h"


UCLASS()
class HUMANITYLASTRESORT_API ANewGrid : public AActor
{
	GENERATED_BODY()

public:
	ANewGrid();

	TArray<FVector> GridPoints;

	FVector closestPos;
	float closestDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* SphereMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cells")
		int GridSize = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cells")
		int WorldGridSize = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cells")
		TSubclassOf<class AActor> ActorToSpawn;

	UFUNCTION(BlueprintCallable, Category = "Cells")
		void PopulateGrid();
	UFUNCTION(BlueprintCallable, Category = "Cells")
		FVector GetClosestPosition(FVector InPosition);


	virtual void PreSave(const class ITargetPlatform* TargetPlatform);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
