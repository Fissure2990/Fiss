// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindActorNode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDEFENCE_API UFindActorNode : public UBTTaskNode
{
	GENERATED_BODY()
	
	UFindActorNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
