// Fill out your copyright notice in the Description page of Project Settings.

#include "FightPawnController.h"
#include "Magician.h"

AMagician::AMagician()
{


	//무기
	{
		Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
		Weapon->SetupAttachment(mSkel, "WeaponSocket");
	}


	//위치 조정
	{
		
		mSkel->SetRelativeLocation(FVector(0, 0, 0));
		mSkel->SetRelativeRotation(FRotator(0, -90.0f, 0));
	}

	//컨트롤러
	{
		AIControllerClass = AFightPawnController::StaticClass();
	}

	//무브먼트
	{

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
				static ConstructorHelpers::FClassFinder<UAnimInstance> Asset(TEXT("AnimBlueprint'/Game/AB/AB_Magician.AB_Magician_C'"));
				if (Asset.Succeeded())
				{
					mSkel->SetAnimInstanceClass(Asset.Class);
				}
		}
	}

}
