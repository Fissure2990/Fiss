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

	virtual void OnPossess(APawn* InPawn);
	

private:



	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;

};
