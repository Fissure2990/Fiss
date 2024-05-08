// Fill out your copyright notice in the Description page of Project Settings.


#include "FightPawnController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


AFightPawnController::AFightPawnController()
{
	{
		static ConstructorHelpers::FObjectFinder<UBlackboardData> Asset(TEXT("BlackboardData'/Game/GameBP/Behavior/FightMonster/LongRanged/LR_BB.LR_BB'"));
		if (Asset.Succeeded())
		{
			BBAsset = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UBehaviorTree> Asset(TEXT("BehaviorTree'/Game/GameBP/Behavior/FightMonster/LongRanged/LR_BT.LR_BT'"));
		if (Asset.Succeeded())
		{
			BTAsset = Asset.Object;
		}
	}


}





void AFightPawnController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BBAsset)
	{

		UBlackboardComponent* BBref = Blackboard;
		if (UseBlackboard(BBAsset, BBref))
		{
			RunBehaviorTree(BTAsset);
		}
	}
}
