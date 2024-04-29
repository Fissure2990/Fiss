// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FightPawnController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDEFENCE_API AFightPawnController : public AAIController
{
	GENERATED_BODY()


	AFightPawnController();
	virtual void BeginPlay();
	virtual void OnPossess(APawn* InPawn);
	virtual void Tick(float DeltaTime);


private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;

};
