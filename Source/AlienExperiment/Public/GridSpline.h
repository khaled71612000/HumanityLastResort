// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "GridSpline.generated.h"

USTRUCT(BlueprintType)
struct FGridSplineBank: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText StructureName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AGridSpline> StructureClassREF;
};



UCLASS()
class HUMANITYLASTRESORT_API AGridSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridSpline();

	UFUNCTION(BlueprintCallable, Category = "Function")
		void AddMeshToSplinePoint(int const& SplinePoint);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Componenets")
	class	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	class UStaticMesh* StaticMeshREF;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		class UMaterial* MaterialREF;

};
