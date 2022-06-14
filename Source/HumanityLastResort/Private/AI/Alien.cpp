
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
	Mood = 100;
}

void AAlien::BeginPlay()
{
	Super::BeginPlay();
	GetComponents(Needs);
	Task = NewObject<UNeedSatisfactionTask>(this);
	AlienSubsystem = GetWorld()->GetSubsystem<UAlienSubsystem>();
}

bool AAlien::TryGetTask()
{
	Needs.Sort([](const UNeedComponent& A, const UNeedComponent& B) {
		return A.CurValue < B.CurValue;
		});

	for (UNeedComponent* Need : Needs)
	{
		if (Task->TrySatisfy(Need, this))
			return true;

	}
	return false;
}

void AAlien::GoToTask()
{
	Task->Satisfy();
}



void AAlien::DoTask()
{
	Task->Wait();
}

void AAlien::Wander()
{
	Task->Wander();
}

void AAlien::Leave()
{
	AAlienAIController* AI = Cast<AAlienAIController>(GetController());
	AI->MoveToLocation(UGameplayStatics::GetActorOfClass(GetWorld(), ATargetPoint::StaticClass())->GetActorLocation(), 5.f);
}

void AAlien::ChangeMood(int MoodVal)
{
	//UE_LOG(LogTemp, Warning, TEXT("Mood: %d"), MoodVal);

	AlienSubsystem->GlobalMood -= Mood;
	Mood += MoodVal;
	if (Mood < 0)
		Mood = 0;
	else if (Mood > 100)
		Mood = 100;
	AlienSubsystem->UpdateGlobalMood(Mood);

}


void AAlien::SetAlienNeedsValues(TArray<AlienNeedsValue*>& NeedsValues)
{
	for (int i = 0; i < NeedsValues.Num(); i++)
	{
		int32 temp = FMath::RandRange(NeedsValues[i]->DecayRate.from, NeedsValues[i]->DecayRate.to);
		Needs[i]->DecayRate = temp;
		Needs[i]->DecayRate = FMath::RandRange(NeedsValues[i]->DecayRate.from, NeedsValues[i]->DecayRate.to);
		Needs[i]->TaskTime = FMath::RandRange(NeedsValues[i]->TimeSpent.from, NeedsValues[i]->TimeSpent.to);
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
