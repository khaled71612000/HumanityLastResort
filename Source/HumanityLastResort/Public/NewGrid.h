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
	// Sets default values for this actor's properties
	ANewGrid();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* SphereMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cells")
	int GridSize = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cells")
	int WorldGridSize = 1000;
	TArray<AActor*> GridArray;
	TArray<FVector> GridPoints;


	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Cells")
	TSubclassOf<class AActor> ActorToSpawn;

	UFUNCTION(BlueprintCallable, Category = "Cells")
	void PopulateGrid();

	UFUNCTION(BlueprintCallable, Category = "Cells")
	FVector GetClosestPosition(FVector InPosition);
	FVector closestPos;
	float closestDistance;

	virtual void PreSave(const class ITargetPlatform* TargetPlatform);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
