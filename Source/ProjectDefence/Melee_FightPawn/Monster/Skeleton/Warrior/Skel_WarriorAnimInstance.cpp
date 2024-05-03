// Fill out your copyright notice in the Description page of Project Settings.


#include "Skel_WarriorAnimInstance.h"
#include "GameFramework/FloatingPawnMovement.h"


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

    UFloatingPawnMovement* FloatingMovement = Cast<UFloatingPawnMovement>(OwningPawn->GetMovementComponent());
    if (!FloatingMovement) return;
    float MaxSpeed = 1.0f;
    MaxSpeed = FloatingMovement->MaxSpeed;

        // 폰의 속도를 계산합니다.
     float CurrentSpeed = OwningPawn->GetVelocity().Size();
     Speed = FMath::Clamp(CurrentSpeed / MaxSpeed, 0.0f, 1.0f);
}

void USkel_WarriorAnimInstance::AnimNotify_AttackEnd()
{
    IsAttack = false;
}

void USkel_WarriorAnimInstance::AnimNotify_Col_On()
{
}

void USkel_WarriorAnimInstance::AnimNotify_Col_Off()
{
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
