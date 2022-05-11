
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EconomySubsystem.generated.h"

UCLASS()
class HUMANITYLASTRESORT_API UEconomySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
	 int32 cash = 0;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
	

	UFUNCTION(BlueprintCallable, Category = "Testing")
	void PrintCash();
	UFUNCTION(BlueprintCallable, Category = "Testing")
		void AddCash();
};
