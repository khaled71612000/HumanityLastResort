// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "AICharacterBase.h"
#include "Hotel.h"
#include "Resturant.h"

void AAIControllerBase::ArrangeHotelsArray()
{
	AAICharacterBase* NPC = Cast<AAICharacterBase>(GetPawn());
	if (!NPC)
		return;
	TArray<AActor*> WorldHotels;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHotel::StaticClass(), WorldHotels);
	
	for (AActor* H : WorldHotels)
	{
		int32 dist = (int32)FVector::Distance(H->GetActorLocation(), NPC->GetActorLocation());
		NPC->Hotels.Add(dist, H);
	}

}

void AAIControllerBase::ArrangeResturantsArray()
{
	AAICharacterBase* NPC = Cast<AAICharacterBase>(GetPawn());
	if (!NPC)
		return;
	TArray<AActor*> WorldResturants;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AResturant::StaticClass(), WorldResturants);

	for (AActor* R : WorldResturants)
	{
		int32 dist = (int32)FVector::Distance(R->GetActorLocation(), NPC->GetActorLocation());
		NPC->Resturants.Add(dist, R);
	}

}

int AAIControllerBase::GetTaskToPerform()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Trying"));
	AAICharacterBase* NPC = Cast<AAICharacterBase>(GetPawn());
	if (!NPC) {
		return -1;
	}
		
	TaskToPerformIndex = -1;
	HighPriority = TNumericLimits<float>::Max();
	TaskPriority = 0.f;

	for (int i = 0; i < NPC->AIState.Num(); i++)
	{
		if ((*((NPC->AIState)[i])))
		{
			TaskPriority = *(NPC->AIAttributes[i]) / 100.f;
			if (TaskPriority < HighPriority)
			{
				HighPriority = TaskPriority;
				TaskToPerformIndex = i;
			}
		}
	}

	return TaskToPerformIndex;

}

void AAIControllerBase::PerformTask()
{
	AAICharacterBase* NPC = Cast<AAICharacterBase>(GetPawn());
	if (!NPC) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Task State: %d"), NPC->TaskState);
	(NPC->*(NPC->Actions[TaskToPerformIndex]))();
}

void AAIControllerBase::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	AAICharacterBase* NPC = Cast<AAICharacterBase>(GetPawn());
	if (NPC) {
		if (NPC->TaskState != Idle)
			NPC->TaskState = Failed;
	}

}
