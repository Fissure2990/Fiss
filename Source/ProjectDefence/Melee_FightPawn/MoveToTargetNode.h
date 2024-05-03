// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToTargetNode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDEFENCE_API UMoveToTargetNode : public UBTTaskNode
{
	GENERATED_BODY()
	
	UMoveToTargetNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
