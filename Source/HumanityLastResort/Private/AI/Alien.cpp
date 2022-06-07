
#include "AI/Alien.h"
#include "AI/NeedComponent.h"
#include "AI/NeedSatisfactionTask.h"
#include "AI/AlienSubsystem.h"
#include "AI/AlienAIController.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"


AAlien::AAlien()
{
	PrimaryActorTick.bCanEverTick = false;
	AlienState = Idle;
	isDancing = false;
}

void AAlien::BeginPlay()
{
	Super::BeginPlay();
	GetComponents(Needs);
	AlienSubsystem = GetWorld()->GetSubsystem<UAlienSubsystem>();
}

void AAlien::GetTask()
{
	int MinValue = 101;
	for (UNeedComponent* Need : Needs)
	{
		if (Need->CurValue < MinValue)
		{
			NeedToExcute = Need;
			MinValue = Need->CurValue;
		}
	}
}

void AAlien::GoToTask()
{
	if (NeedToExcute)
		NeedToExcute->Task->Satisfy(this, NeedToExcute);
	else
		AlienState = Idle;
}

void AAlien::DoTask()
{
	if (NeedToExcute)
		NeedToExcute->Task->Wait();

}

void AAlien::Leave()
{
	AAlienAIController* AI = Cast<AAlienAIController>(GetController());
	AI->MoveToLocation(UGameplayStatics::GetActorOfClass(GetWorld(), ATargetPoint::StaticClass())->GetActorLocation(), 5.f);
}

void AAlien::ChangeMood(int MoodVal)
{
	AlienSubsystem->GlobalMood -= Mood;
	Mood += MoodVal;
	AlienSubsystem->GlobalMood += Mood;
	AlienSubsystem->UpdateGlobalMood();

}


void AAlien::SetAlienNeedsValues(TArray<AlienNeedsValue*>& NeedsValues)
{
	for (int i = 0; i < NeedsValues.Num(); i++)
	{
		int32 temp = FMath::RandRange(NeedsValues[i]->DecayRate.from, NeedsValues[i]->DecayRate.to);
		Needs[i]->DecayRate = temp;
		UE_LOG(LogTemp, Warning, TEXT("Temp: %d"), temp);

		UE_LOG(LogTemp, Warning, TEXT("DecayRate: %d"), Needs[i]->DecayRate);
		UE_LOG(LogTemp, Warning, TEXT("DecayRateFrom: %d"), NeedsValues[i]->DecayRate.from);
		UE_LOG(LogTemp, Warning, TEXT("DecayRateTo: %d"), NeedsValues[i]->DecayRate.to);

		Needs[i]->DecayRate = FMath::RandRange(NeedsValues[i]->DecayRate.from, NeedsValues[i]->DecayRate.to);
		Needs[i]->TaskTime = FMath::RandRange(NeedsValues[i]->TimeSpent.from, NeedsValues[i]->TimeSpent.to);

		
		UE_LOG(LogTemp, Warning, TEXT("TaskTime: %d"), Needs[i]->TaskTime);
		UE_LOG(LogTemp, Warning, TEXT("TaskTimefrom: %d"), NeedsValues[i]->TimeSpent.from);
		UE_LOG(LogTemp, Warning, TEXT("TaskTimeTo: %d"), NeedsValues[i]->TimeSpent.to);

	}
}

void AAlien::SetAlienAttributes(AlienAttributes AlienAttributes)
{
	GoodMoodVal = FMath::RandRange(AlienAttributes.GoodMoodVal.from, AlienAttributes.GoodMoodVal.to);
	BadMoodVal = FMath::RandRange(AlienAttributes.BadMoodVal.from, AlienAttributes.BadMoodVal.to);
	NumOfTasks = FMath::RandRange(AlienAttributes.NumOfTasks.from, AlienAttributes.NumOfTasks.to);
	NumOfTasks = FMath::RandRange(AlienAttributes.NumOfTasks.from, AlienAttributes.NumOfTasks.to);
}

void AAlien::AddAlienToPool()
{
	AlienSubsystem->AliensPool[AlienType].Add(this);
}

void AAlien::CallSetAlienNeedsValues()
{
}
void AAlien::CallSetAlienAttributes()
{

}

bool AAlien::GetisDancing()
{
	return isDancing;
}
