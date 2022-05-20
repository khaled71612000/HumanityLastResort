// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NeedSatisfactionTask.generated.h"

/**
 * 
 */
UCLASS()
class HUMANITYLASTRESORT_API UNeedSatisfactionTask : public UObject
{
	GENERATED_BODY()

public:
	virtual void Satisfy();

};
