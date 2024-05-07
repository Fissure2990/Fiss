#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "../FightPawnBase.h"
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
	AFightPawnBase* Target;

	float Distance;
};
