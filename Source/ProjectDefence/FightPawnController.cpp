// Fill out your copyright notice in the Description page of Project Settings.


#include "FightPawnController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


AFightPawnController::AFightPawnController()
{
	{
		static ConstructorHelpers::FObjectFinder<UBlackboardData> Asset(TEXT("BlackboardData'/Game/Behavior/FightMonster/LongRanged/LR_BB.LR_BB'"));
		if (Asset.Succeeded())
		{
			BBAsset = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UBehaviorTree> Asset(TEXT("BehaviorTree'/Game/Behavior/FightMonster/LongRanged/LR_BT.LR_BT'"));
		if (Asset.Succeeded())
		{
			BTAsset = Asset.Object;
		}
	}
}



void AFightPawnController::BeginPlay()
{
	Super::BeginPlay();

	//ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//if (PlayerCharacter)
	//{
	//	SetFocus(PlayerCharacter);
	//}
}

void AFightPawnController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "tes1t");
	if (BBAsset)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "test");
		UBlackboardComponent* BBref = Blackboard;
		if (UseBlackboard(BBAsset, BBref))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "test3");
			RunBehaviorTree(BTAsset);
		}
	}
}

void AFightPawnController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//float Distance = GetPawn()->GetDistanceTo(PlayerCharacter);

	//GetBlackboardComponent()->SetValueAsFloat(TEXT("Distance"), Distance);
	//AActor* FocusedActor = GetFocusActor();


}

