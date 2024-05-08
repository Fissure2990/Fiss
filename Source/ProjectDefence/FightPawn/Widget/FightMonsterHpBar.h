// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../FightPawnBase.h"
#include "Blueprint/UserWidget.h"
#include "FightMonsterHpBar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDEFENCE_API UFightMonsterHpBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	AFightPawnBase* FP;

};
