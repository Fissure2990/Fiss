// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../FightPawn/FightPawnBase.h"
#include "Magician.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDEFENCE_API AMagician : public AFightPawnBase
{
	GENERATED_BODY()
	
	AMagician();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Weapon;

	virtual void Death() override;

};
