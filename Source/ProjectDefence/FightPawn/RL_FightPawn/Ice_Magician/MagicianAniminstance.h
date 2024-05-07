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
	UAnimMontage* Death;
	
	bool IsAttack = false;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	//노티파이
	UFUNCTION()
	void AnimNotify_AttackEnd();
	UFUNCTION()
	void AnimNotify_Shooting();
	UFUNCTION()
	void AnimNotify_PauseMontage();
public:
	void OnAttack();

	void OnDie();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;

};
