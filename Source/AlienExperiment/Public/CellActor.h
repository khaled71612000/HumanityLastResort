// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "CellActor.generated.h"

USTRUCT(BlueprintType)
struct FBlankCellInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int x{};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int y{};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int z{};

	FBlankCellInfo() = default;
	FBlankCellInfo(int const NewX, int const NewY,int const NewZ)
		: x(NewX), y(NewY), z(NewZ)
	{
	}
};

UENUM(BlueprintType)
enum class EBGActorType : uint8
{
	None UMETA(DisplayName = "None"),
	Building UMETA(DisplayName = "Building"),
	Road UMETA(DisplayName = "Road"),
};


UCLASS()
class HUMANITYLASTRESORT_API ACellActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACellActor();

	void SetCellInfo(FBlankCellInfo InCellInfo) {
		CellInfo = InCellInfo;
	}

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Category = "config", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FBlankCellInfo CellInfo;

	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* StaticMeshComponent;

};
