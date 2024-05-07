// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Skel_WarriorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDEFENCE_API USkel_WarriorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	USkel_WarriorAnimInstance();

private:


	UAnimMontage* Attack;
	UAnimMontage* Death;

	bool IsAttack = false;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	//노티파이
	UFUNCTION()
	void AnimNotify_AttackEnd();
	UFUNCTION()
	void AnimNotify_WeaponCollisionStart();
	UFUNCTION()
	void AnimNotify_WeaponCollisionEnd();
	UFUNCTION()
	void AnimNotify_PauseMontage();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;

	void OnAttack();

	void OnDie();

};
