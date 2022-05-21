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

	int GridSize = 10;
	int WorldGridSize = 1000;
	TArray<AActor*> GridArray;

	UFUNCTION(BlueprintCallable, Category = "Cells")
	void PopulateGrid();

	virtual void PreSave(const class ITargetPlatform* TargetPlatform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
