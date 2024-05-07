// Fill out your copyright notice in the Description page of Project Settings.


#include "Skel_Warrior.h"
#include "Skel_WarriorAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../../../Melee_FightPawnController.h"

ASkel_Warrior::ASkel_Warrior()
{
	//무기
	{

		Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
		WeaponCol = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollision"));

		Weapon->SetupAttachment(mSkel, "WeaponSocket");
		WeaponCol->SetupAttachment(mSkel, "WeaponCol");

		WeaponCol->SetCapsuleHalfHeight(50.0f);
		WeaponCol->SetCapsuleRadius(35.0f);
		
		WeaponCol->OnComponentBeginOverlap.AddDynamic(this, &ASkel_Warrior::OnBeginOverlap);

		
	}


	//스켈 및 캡슐 위치 조정
	{

		mSkel->SetRelativeLocation(FVector(0, 0, -80.0f));
		mSkel->SetRelativeRotation(FRotator(0, -90.0f, 0));
		//mCapsule->SetRelativeLocation(FVector(0, 0, 80));
	}
	//캡슐 크기 조정
	{
		mCapsule->SetCapsuleHalfHeight(90.0f);
		mCapsule->SetCapsuleRadius(50.0f);
	}

	//컨트롤러
	{
		AIControllerClass = AMelee_FightPawnController::StaticClass();
	}

	//태그
	{
		Tags.Add(TEXT("Enemy"));
	}

	{
		//몸통
		{
			static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/GameBP/MonsterAsset/Skeleton/Warrior/Skeleton_Warrior.Skeleton_Warrior'"));
			if (Asset.Succeeded())
			{
				mSkel->SetSkeletalMesh(Asset.Object);
			}
		}
		//무기
		{
			static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/GameBP/MonsterAsset/Skeleton/Warrior/Weapon/Skeleton_Axe.Skeleton_Axe'"));
			if (Asset.Succeeded())
			{
				Weapon->SetStaticMesh(Asset.Object);
			}
		}
		//애니메이션
		{
			static ConstructorHelpers::FClassFinder<UAnimInstance> Asset(TEXT("/Script/Engine.AnimBlueprint'/Game/GameBP/AB/Monster/Skeleton/Warrior/SW_Animation.SW_Animation_C'"));
			if (Asset.Succeeded())
			{
				mSkel->SetAnimInstanceClass(Asset.Class);
			}
		}
	}

	mCapsule->SetCollisionProfileName("PawnBase");
	Weapon->SetCollisionProfileName("NoCollision");
	WeaponCol->SetCollisionProfileName("NoCollision");
}

void ASkel_Warrior::Death()
{
	Super::Death();

	auto Anim = Cast<USkel_WarriorAnimInstance>(mSkel->GetAnimInstance());

	Anim->OnDie();

	IsDying = true;

	AAIController* AIC = Cast<AAIController>(GetController());

	AIC->GetBlackboardComponent()->SetValueAsBool("OnDie", IsDying);
	
	AIC->StopMovement();

	mCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASkel_Warrior::Attack()
{
	Super::Attack();

	USkel_WarriorAnimInstance* AnimInstance = Cast<USkel_WarriorAnimInstance>(mSkel->GetAnimInstance());
	if (AnimInstance)
	{
		AAIController* AIC = Cast<AAIController>(GetController());
		if (AIC)
		{
			AActor* Target = Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("EnemyActor"));
			if (!Target)
			{
				return;
			}

			AnimInstance->OnAttack();
			AIC->StopMovement();
		}


		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "BTATTACK");
	}

}

void ASkel_Warrior::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool OnlyOneDamage = false;

	//if (!Master && !Damage) return;

	if (Other && OnlyOneDamage == false)
	{
		// 태그가 있는지 확인
		if (Other->Tags.Num() > 0)
		{
			if (Tags[0] == Other->Tags[0])
			{

			}
			else if (Tags[0] != Other->Tags[0])
			{
				AFightPawnBase* Enemy = Cast<AFightPawnBase>(Other);
				if (Enemy)
				{
					Enemy->GetDamage(Damage);
					OnlyOneDamage = true;
				}
			}
			else
			{
				return;
			}
		}

	}

}

