// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AttackNode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDEFENCE_API UAttackNode : public UBTTaskNode
{
	GENERATED_BODY()

	UAttackNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
