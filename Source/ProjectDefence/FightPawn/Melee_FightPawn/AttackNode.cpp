// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackNode.h"
#include "../FightPawnBase.h"
#include "AiController.h"

UAttackNode::UAttackNode()
{
	NodeName = "Melee_Attack";
}

EBTNodeResult::Type UAttackNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	AFightPawnBase* ControlledPawn = Cast<AFightPawnBase>(AIController->GetPawn());
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	ControlledPawn->Attack();

	return EBTNodeResult::Type();
}
