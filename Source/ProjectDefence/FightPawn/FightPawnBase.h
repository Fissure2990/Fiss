// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "FightPawnBase.generated.h"

UCLASS()
class PROJECTDEFENCE_API AFightPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFightPawnBase();

public:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mSkel;
protected:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
	UAIPerceptionStimuliSourceComponent* Sencer;
};
