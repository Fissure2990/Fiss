// Fill out your copyright notice in the Description page of Project Settings.


#include "FindActorNode.h"
#include "FightPawnController.h"
#include "AIController.h"

UFindActorNode::UFindActorNode()
{
	NodeName = "FindEnemy";
}

EBTNodeResult::Type UFindActorNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AFightPawnController* AIController = Cast<AFightPawnController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "FindEnemy");
		AIController->EnemyFind();
	}
	else
	{
		return EBTNodeResult::Failed;
	}


	return EBTNodeResult::Type();
}
