// Fill out your copyright notice in the Description page of Project Settings.

#include "Magician.h"
#include "MagicianAniminstance.h"
#include "../FightPawnController.h"
#include "BehaviorTree/BlackBoardComponent.h"


AMagician::AMagician()
{
	//무기
	{
		Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
		Weapon->SetupAttachment(mSkel, "WeaponSocket");
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
		AIControllerClass = AFightPawnController::StaticClass();
	}

	//태그
	{
		Tags.Add(TEXT("Team"));
	}

	{
		//몸통
		{
			static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/BattleWizardPolyart/Meshes/WizardSM.WizardSM'"));
			if (Asset.Succeeded())
			{
				mSkel->SetSkeletalMesh(Asset.Object);
			}
		}
		//무기
		{
			static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/BattleWizardPolyart/Meshes/MagicStaffs/Staff01SM.Staff01SM'"));
			if (Asset.Succeeded())
			{
				Weapon->SetStaticMesh(Asset.Object);
			}
		}
		//애니메이션
		{
				static ConstructorHelpers::FClassFinder<UAnimInstance> Asset(TEXT("/Script/Engine.AnimBlueprint'/Game/GameBP/AB/Magician/AB_Magician.AB_Magician_C'"));
				if (Asset.Succeeded())
				{
					mSkel->SetAnimInstanceClass(Asset.Class);
				}
		}
	}

	Weapon->SetCollisionProfileName("NoCollision");
}

void AMagician::Death()
{
	Super::Death();

	auto Anim = Cast<UMagicianAniminstance>(mSkel->GetAnimInstance());

	Anim->OnDie();

	IsDying = true;

	AAIController* AIC = Cast<AAIController>(GetController());

	AIC->GetBlackboardComponent()->SetValueAsBool("OnDie", IsDying);

	AIC->StopMovement();

	mCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}
