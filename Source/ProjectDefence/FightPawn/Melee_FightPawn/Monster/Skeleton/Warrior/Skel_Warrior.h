// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../../FightPawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Skel_Warrior.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDEFENCE_API ASkel_Warrior : public AFightPawnBase
{
	GENERATED_BODY()
	
	ASkel_Warrior();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Weapon;
public:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* WeaponCol;
private:
	virtual void Death() override;
	virtual void Attack() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
