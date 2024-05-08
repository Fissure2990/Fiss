// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToTargetNode.h"
#include "AIController.h"
#include "../FightPawnBase.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


UMoveToTargetNode::UMoveToTargetNode()
{
	NodeName = "MoveToTarget";
}

EBTNodeResult::Type UMoveToTargetNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	AActor* Target = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("EnemyActor"));
	if (!Target)
	{
		return EBTNodeResult::Failed;
	}
	//AIController->MoveToActor(Target);



	AIController->MoveToLocation(Target->GetActorLocation());
	return EBTNodeResult::Type();
}
