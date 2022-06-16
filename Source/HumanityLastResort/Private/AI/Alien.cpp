
#include "AI/Alien.h"
#include "AI/NeedComponent.h"
#include "AI/NeedSatisfactionTask.h"
#include "AI/AlienSubsystem.h"

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
	Task->CustomBeginPlay();
	AlienSubsystem = GetWorld()->GetSubsystem<UAlienSubsystem>();
}

void AAlien::TryGetTask()
{
	Needs.Sort([](const UNeedComponent& A, const UNeedComponent& B) {
		return A.CurValue < B.CurValue;
		});

	for (UNeedComponent* Need : Needs)
	{
		if (Need->CurValue < Need->Threshold)
		{
			if (Task->TrySatisfy(Need, this)) 
			{
				GoToTask();
				return;
			}
			else
			{
				NumOfFailedTasks--;
				ChangeMood(-BadMoodVal);
				if (NumOfFailedTasks <= 0)
				{
					AlienState = Leaving;
					return;
				}
			}
		}
	}
	AlienState = Wandering;
	Wander();
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
	Task->Wander(this);
}

void AAlien::Leave()
{
	Task->Leave(this);
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
	AlienSubsystem->UpdateGlobalMoodPercentage();
}


void AAlien::AddAlienToPool()
{
	for (int32 i = 0; i < Needs.Num(); i++)
	{
		Needs[i]->CurValue = Needs[i]->MaxCapacity;
	}
	AlienState = Idle;
	AlienSubsystem->AliensPool[AlienType].Aliens.Add(this);
}

bool AAlien::GetisDancing()
{
	return isDancing;
}
