// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
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
	virtual void OnPossess(APawn* InPawn);
	virtual void Tick(float DeltaTime);


private:


	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> Targets;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* Perception;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sight")
	UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UPROPERTY(EditAnywhere)
	AActor* Target;
    

	UPROPERTY(EditAnywhere)
	float Distance;
};
