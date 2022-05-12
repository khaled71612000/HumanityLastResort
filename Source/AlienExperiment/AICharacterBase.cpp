// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Resturant.h"
#include "Hotel.h"
#include "AIControllerBase.h"

// Sets default values
AAICharacterBase::AAICharacterBase()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SSMeshRef(TEXT("SkeletalMesh'/Engine/Tutorial/SubEditors/TutorialAssets/Character/TutorialTPP.TutorialTPP'"));
	if (SSMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SSMeshRef.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	PrimaryActorTick.bCanEverTick = true;
	NotHungry = 100;
	NotSleepy = 100;
	isHungry = false;
	isSleepy = false;
	DoingTask = false;

	//AIState.Add(&isHungry);
	AIState.Add(&isSleepy);
	//AIAttributes.Add(&NotHungry);
	AIAttributes.Add(&NotSleepy);
	//Actions.Add(&AAICharacterBase::MoveToResturant);
	Actions.Add(&AAICharacterBase::MoveToHotel);


	TaskState = Idle;

};
	


// Called when the game starts or when spawned
void AAICharacterBase::BeginPlay()
{
	Super::BeginPlay();
	//AI = Cast<AAIControllerBase>(GetController());

	//GettingHungry();
	GettingSleepy();
}

void AAICharacterBase::Tick(float DeltaTime)
{
	AAIControllerBase* AI = Cast<AAIControllerBase>(GetController());
	if (!AI) 
		return;
	
	if (AI && TaskState == Idle)
	{
		TaskInd = AI->GetTaskToPerform();
		if(TaskInd != -1)
			TaskState = Assigned;
	}

	if (TaskInd != -1 && (TaskState == Assigned || TaskState == Failed)) {
		UE_LOG(LogTemp, Warning, TEXT("Task State before calling %d: "), TaskState);
		TaskState = Moving;
		AI->PerformTask();
	}
}

void AAICharacterBase::GettingHungry()
{
	GetWorld()->GetTimerManager().SetTimer(HungryManager, this, &AAICharacterBase::ChangeNotHungryAttr, 1.0f, true);
}

void AAICharacterBase::GettingSleepy()
{	
	GetWorld()->GetTimerManager().SetTimer(SleepyManager, this, &AAICharacterBase::ChangeNotSleepyAttr, 1.0f, true);
}

void AAICharacterBase::ChangeNotHungryAttr()
{

	if (NotHungry > 0)
		NotHungry -= 1;

	if (NotHungry < 95) {
		MoveToResturant();
	}

	UE_LOG(LogTemp, Warning, TEXT("Not Hungry: %d"), NotHungry);
}

void AAICharacterBase::ChangeNotSleepyAttr()
{
	if (NotSleepy > 0)
		NotSleepy -= 1;

	if (NotSleepy < 98)
	{
		isSleepy = true;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Not Sleepy: %d"), NotSleepy);

}


// Called to bind functionality to input
void AAICharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacterBase::MoveToResturant()
{
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AResturant::StaticClass(), Resturants);

	//AAIController* AI = Cast<AAIController>(GetController());
	//if (!AI)
	//	return;

	//for (AActor* Resturant : Resturants)
	//{
	//	AResturant* Rest = Cast<AResturant>(Resturant);

	//	if (Rest && Rest->Residents < Rest->Capacity)
	//	{
	//		AI->MoveTo(Rest->GetActorLocation());
	//		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Moving"));
	//	}
	//}
}

void AAICharacterBase::MoveToHotel()
{		
	UE_LOG(LogTemp, Warning, TEXT("Task State after calling: %d"), TaskState);
	AAIControllerBase* AI = Cast<AAIControllerBase>(GetController());
	if (!AI)
		return;

	AI->ArrangeHotelsArray();

	for (auto& Hotel : Hotels)
	{
		AHotel* Hot = Cast<AHotel>(Hotel.Value);
		if (Hot && Hot->Residents < Hot->Capacity)
		{
			AI->MoveTo(Hot->GetActorLocation());
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Called"));

			Hot->Residents += 1;
			break;
		}

		//UE_LOG(LogTemp, Warning, TEXT("Hotels: %d"), Hotels.Num());
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Look"));
	}

}
