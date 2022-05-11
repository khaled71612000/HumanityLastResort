// Fill out your copyright notice in the Description page of Project Settings.


#include "EconomySubsystem.h"

 void UEconomySubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	 cash = 0;
}

 void UEconomySubsystem::Deinitialize() {
 }
  
 void UEconomySubsystem::PrintCash() {
	 UE_LOG(LogTemp, Error, TEXT("GAME INSTANCE %d"),cash);
 }
 void UEconomySubsystem::AddCash() {
	 cash++;
 }