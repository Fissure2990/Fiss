// Fill out your copyright notice in the Description page of Project Settings.


#include "PJ_SpikeBase.h"

// Sets default values
APJ_SpikeBase::APJ_SpikeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));

	SetRootComponent(Effect);

	SetLifeSpan(1.5f);
}

void APJ_SpikeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

