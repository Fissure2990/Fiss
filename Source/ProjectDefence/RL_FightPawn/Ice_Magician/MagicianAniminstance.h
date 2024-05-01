// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MagicianAniminstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDEFENCE_API UMagicianAniminstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:

	UMagicianAniminstance();

	UAnimMontage* Attack;
	
	bool IsAttack = false;

	//노티파이
	UFUNCTION()
	void AnimNotify_AttackEnd();
	UFUNCTION()
	void AnimNotify_Shooting();

public:
	void OnAttack();


};
