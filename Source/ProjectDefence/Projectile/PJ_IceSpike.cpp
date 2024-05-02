// Fill out your copyright notice in the Description page of Project Settings.


#include "PJ_IceSpike.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

APJ_IceSpike::APJ_IceSpike()
{
    {
        static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Assset(TEXT("NiagaraSystem'/Game/VFX_MagicProjectile/Niagaras/NS_IceImpact.NS_IceImpact'"));
        if (Assset.Succeeded())
        {
            Effect->SetAsset(Assset.Object);
        }
    }


}
