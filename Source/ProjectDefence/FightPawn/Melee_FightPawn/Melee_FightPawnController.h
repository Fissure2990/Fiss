// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "../FightPawnBase.h"
#include "AIController.h"
#include "Melee_FightPawnController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDEFENCE_API AMelee_FightPawnController : public AAIController
{
	GENERATED_BODY()
	

	AMelee_FightPawnController();
	virtual void BeginPlay();
	virtual void Tick(float Time);
	virtual void OnPossess(APawn* InPawn);


private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;

	//UPROPERTY(VisibleAnywhere)
	//class UCrowdFollowingComponent* CrowdComp;

};
