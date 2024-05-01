// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicianAniminstance.h"
#include "Magician.h"
#include "../../Projectile/PJ_Magic_Ice.h"
#include "../../FightPawn/FightPawnController.h"
#include "GameFramework/Character.h"

UMagicianAniminstance::UMagicianAniminstance()
{
    {
        static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAss(TEXT("/Script/Engine.AnimMontage'/Game/AB/Magician_Attack.Magician_Attack'"));
        if (AttackAss.Succeeded())
        {
            Attack = AttackAss.Object;
        }
    }
}

void UMagicianAniminstance::OnAttack()
{
    if (IsAttack) return;

    Montage_Play(Attack);

    IsAttack = true;
 }

void UMagicianAniminstance::AnimNotify_AttackEnd()
{
    IsAttack = false;
}

void UMagicianAniminstance::AnimNotify_Shooting()
{
    AMagician* Char = Cast<AMagician>(TryGetPawnOwner());
    if (!Char) return;
   FTransform SocketTransform = Char->mSkel->GetSocketTransform("ShootPoint", RTS_World);
   FVector SocketLocation = SocketTransform.GetLocation();
   FRotator SocketRotation = SocketTransform.GetRotation().Rotator();
   
   AFightPawnController* FPC = Cast<AFightPawnController>(Char->GetController());
   AActor* Target = FPC->Target;
   if (!Target) return;

   FVector Direction = (Target->GetActorLocation() - SocketLocation).GetSafeNormal();
   // 회전 계산
   FRotator ProjectileRotation = FRotationMatrix::MakeFromX(Direction).Rotator();


   APJ_Magic_Ice* Projectile = GetWorld()->SpawnActor<APJ_Magic_Ice>(
       APJ_Magic_Ice::StaticClass(),
       SocketLocation,
       ProjectileRotation
   );

  //FVector NewDirection = (Target->GetActorLocation() - Projectile->GetActorLocation()).GetSafeNormal();
 // Projectile->Movement->Velocity = NewDirection * Projectile->Movement->InitialSpeed;
}
