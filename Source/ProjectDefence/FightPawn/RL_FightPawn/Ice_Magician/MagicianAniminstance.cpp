// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicianAniminstance.h"
#include "Magician.h"
#include "../../../Projectile/ProjectileBase.h"
#include "../../../Projectile/PJ_Magic_Ice.h"
#include "GameFramework/Character.h"

UMagicianAniminstance::UMagicianAniminstance()
{
    //공격
    {
        static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAss(TEXT("/Script/Engine.AnimMontage'/Game/GameBP/AB/Magician/Magician_Attack.Magician_Attack'"));
        if (AttackAss.Succeeded())
        {
            Attack = AttackAss.Object;
        }
    }
    //사망
    {
        static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathAss(TEXT("/Script/Engine.AnimMontage'/Game/GameBP/AB/Magician/Magician_Death.Magician_Death'"));
        if (DeathAss.Succeeded())
        {
            Death = DeathAss.Object;
        }
    }
}

void UMagicianAniminstance::OnAttack()
{
    if (IsAttack) return;

    Montage_Play(Attack);

    IsAttack = true;
 }

void UMagicianAniminstance::OnDie()
{ 
    Montage_Play(Death);
 
    IsAttack = true;
}



void UMagicianAniminstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

     APawn* OwningPawn = TryGetPawnOwner();

     UFloatingPawnMovement* FloatingMovement = Cast<UFloatingPawnMovement>(OwningPawn->GetMovementComponent());

     float MaxSpeed = 1.0f;

     // 컴포넌트의 최대 속도를 가져옵니다.
     if (FloatingMovement)
     {
         MaxSpeed = FloatingMovement->MaxSpeed;
     }

    if (OwningPawn)
    {
        // 폰의 속도를 계산합니다.
        float CurrentSpeed = OwningPawn->GetVelocity().Size();
        Speed = FMath::Clamp(CurrentSpeed / MaxSpeed, 0.0f, 1.0f);
    }
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
   
   AActor* Target = Char->Target;
   if (!Target) return;

   FVector Direction = (Target->GetActorLocation() - SocketLocation).GetSafeNormal();
   // 회전 계산
   FRotator ProjectileRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

   //소환
   APJ_Magic_Ice* Projectile = GetWorld()->SpawnActor<APJ_Magic_Ice>(
       APJ_Magic_Ice::StaticClass(),
       SocketLocation,
       ProjectileRotation
   );   
   if (!Projectile) return;

   //변수 설정
   Projectile->Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

   // 변수 설정
   Projectile->Damage = Char->Damage;
   Projectile->Master = Char;

   // 충돌 컴포넌트 다시 활성화
   Projectile->Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


  //FVector NewDirection = (Target->GetActorLocation() - Projectile->GetActorLocation()).GetSafeNormal();
 // Projectile->Movement->Velocity = NewDirection * Projectile->Movement->InitialSpeed;
}

void UMagicianAniminstance::AnimNotify_PauseMontage()
{
    Montage_Pause();
}
