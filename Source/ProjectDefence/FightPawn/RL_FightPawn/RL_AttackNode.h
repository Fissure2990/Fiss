// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RL_AttackNode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDEFENCE_API URL_AttackNode : public UBTTaskNode
{
	GENERATED_BODY()
	
	URL_AttackNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
