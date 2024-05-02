// Fill out your copyright notice in the Description page of Project Settings.


#include "PJ_Magic_Ice.h"
#include "NiagaraComponent.h"
#include "PJ_IceSpike.h"
#include "NiagaraSystem.h"

// Sets default values
APJ_Magic_Ice::APJ_Magic_Ice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //얼음 
    {
        static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Asset(TEXT("NiagaraSystem'/Game/VFX_MagicProjectile/Niagaras/NS_IceProjectile.NS_IceProjectile'"));
        if (Asset.Succeeded())
        {
            Effect->SetAsset(Asset.Object);
        }
    }


}

// Called when the game starts or when spawned
void APJ_Magic_Ice::BeginPlay()
{
	Super::BeginPlay();
	

}

void APJ_Magic_Ice::SpawnSpike()
{
    Super::SpawnSpike();

    FVector Location = GetActorLocation();
    FRotator Rotation = GetActorRotation();

    APJ_IceSpike* Projectile = GetWorld()->SpawnActor<APJ_IceSpike>(
        APJ_IceSpike::StaticClass(),
        Location,
        Rotation
    );

}
