// Fill out your copyright notice in the Description page of Project Settings.


#include "Skel_WarriorAnimInstance.h"
#include "Skel_Warrior.h"
#include "GameFramework/CharacterMovementComponent.h"



USkel_WarriorAnimInstance::USkel_WarriorAnimInstance()
{
    //공격
    {
        static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackAss(TEXT("/Script/Engine.AnimMontage'/Game/GameBP/AB/Monster/Skeleton/Warrior/SW_Attack.SW_Attack'"));
        if (AttackAss.Succeeded())
        {
            Attack = AttackAss.Object;
        }
    }
    //사망
    {
        static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathAss(TEXT("/Script/Engine.AnimMontage'/Game/GameBP/AB/Monster/Skeleton/Warrior/Sw_Death.Sw_Death'"));
        if (DeathAss.Succeeded())
        {
            Death = DeathAss.Object;
        }
    }
}

void USkel_WarriorAnimInstance::OnAttack()
{
    if (IsAttack) return;

    Montage_Play(Attack);

    IsAttack = true;
}



void USkel_WarriorAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    APawn* OwningPawn = TryGetPawnOwner();

    if (!OwningPawn) return;

    UCharacterMovementComponent* FloatingMovement = Cast<UCharacterMovementComponent>(OwningPawn->GetMovementComponent());
    if (!FloatingMovement) return;
    float MaxSpeed = 1.0f;
    MaxSpeed = FloatingMovement->GetMaxSpeed();

        // 폰의 속도를 계산합니다.
     float CurrentSpeed = OwningPawn->GetVelocity().Size();
     Speed = FMath::Clamp(CurrentSpeed / MaxSpeed, 0.0f, 1.0f);
}

void USkel_WarriorAnimInstance::AnimNotify_AttackEnd()
{
    IsAttack = false;
}

void USkel_WarriorAnimInstance::AnimNotify_WeaponCollisionStart()
{
    ASkel_Warrior* Pawn = Cast<ASkel_Warrior>(TryGetPawnOwner());
    if (!Pawn) return;
    Pawn->WeaponCol->SetCollisionProfileName("OverlapOnlyPawn");
}

void USkel_WarriorAnimInstance::AnimNotify_WeaponCollisionEnd()
{
    ASkel_Warrior* Pawn = Cast<ASkel_Warrior>(TryGetPawnOwner());
    if (!Pawn) return;
    Pawn->WeaponCol->SetCollisionProfileName("NoCollision");
}


void USkel_WarriorAnimInstance::OnDie()
{
    Montage_Play(Death);

    IsAttack = true;
}

void USkel_WarriorAnimInstance::AnimNotify_PauseMontage()
{
    Montage_Pause();
}

