// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "FightPawnBase.generated.h"

UCLASS()
class PROJECTDEFENCE_API AFightPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFightPawnBase();
	virtual void BeginPlay();

public:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mSkel;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	UDataTable* CS_Table;
	
	//스탯
		UPROPERTY(VisibleAnywhere)
		int32 Health = 0;

		UPROPERTY(VisibleAnywhere)
		int32 Gage = 0;

		UPROPERTY(VisibleAnywhere)
		int32 Armor = 0;

		UPROPERTY(VisibleAnywhere)
		int32 Damage = 0;
	//데미지
		void GetDamage(int32 Damages);
		virtual void Death();
		virtual void Attack();
protected:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
	UAIPerceptionStimuliSourceComponent* Sencer;


public:
	bool IsDying = false;
	UPROPERTY(EditAnywhere)
	UWidgetComponent* Widget;
};
