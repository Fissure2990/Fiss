// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "StatDataTable.generated.h"


USTRUCT(BlueprintType)
struct FCharacterStats : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinGage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxGage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinArmor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxArmor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackRange;

};

UCLASS()
class PROJECTDEFENCE_API AStatDataTable : public AActor
{
	GENERATED_BODY()
	
};
