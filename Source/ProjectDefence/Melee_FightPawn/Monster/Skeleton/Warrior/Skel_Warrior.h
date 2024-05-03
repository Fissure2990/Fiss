// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../../FightPawn/FightPawnBase.h"
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

	virtual void Death() override;
	virtual void Attack() override;
};
