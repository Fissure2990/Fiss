// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "PJ_Magic_Ice.generated.h"

UCLASS()
class PROJECTDEFENCE_API APJ_Magic_Ice : public AProjectileBase
{
	GENERATED_BODY()
	
public:	
	APJ_Magic_Ice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
