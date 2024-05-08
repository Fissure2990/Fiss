// Fill out your copyright notice in the Description page of Project Settings.


#include "Melee_FightPawnController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include  "Navigation/CrowdManager.h"
#include "Navigation/CrowdFollowingComponent.h"

AMelee_FightPawnController::AMelee_FightPawnController()
{
	{
		static ConstructorHelpers::FObjectFinder<UBlackboardData> Asset(TEXT("/Script/AIModule.BlackboardData'/Game/GameBP/Behavior/FightMonster/Melee/Melee_BB.Melee_BB'"));
		if (Asset.Succeeded())
		{
			BBAsset = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UBehaviorTree> Asset(TEXT("/Script/AIModule.BehaviorTree'/Game/GameBP/Behavior/FightMonster/Melee/Melee_BT.Melee_BT'"));
		if (Asset.Succeeded())
		{
			BTAsset = Asset.Object;
		}
	}
}

void AMelee_FightPawnController::BeginPlay()
{
	Super::BeginPlay();

	//CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	//if (CrowdComp)
	//{
	//	// 군중 시뮬레이션 활성화
	//	//CrowdComp->SetCrowdSimulationState(ECrowdSimulationState::Enabled);

	//	// 분리 행동 활성화 및 가중치 설정
	//	//CrowdComp->SetCrowdSeparation(true);
	//}

}


void AMelee_FightPawnController::OnPossess(APawn* InPawn)
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