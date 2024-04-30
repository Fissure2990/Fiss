// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController.h"
#include "RL_AttackNode.h"
#include "MagicianAniminstance.h"

URL_AttackNode::URL_AttackNode()
{
	NodeName = "RL_Attack";
}

EBTNodeResult::Type URL_AttackNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	APawn* ControlledPawn = AIController->GetPawn();
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	UMagicianAniminstance* AnimInstance = Cast<UMagicianAniminstance>(ControlledPawn->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance());
	if (AnimInstance)
	{
		AIController->StopMovement();
		AnimInstance->OnAttack();
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "BTATTACK");
	}
	else
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Type();
}
