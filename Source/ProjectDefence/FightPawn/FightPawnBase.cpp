// Fill out your copyright notice in the Description page of Project Settings.


#include "FightPawnBase.h"
#include "StatDataTable.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AFightPawnBase::AFightPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	


	//생성
	{
		mSkel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainSkel"));
		mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MainCapsule"));
		Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
		Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
		Sencer = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Sencer"));
	}
	//루트
	{
		RootComponent = mCapsule;
		mSkel->SetupAttachment(mCapsule);
		Widget->SetupAttachment(RootComponent);
	}
	//센서
	{
		//Sencer->bAutoRegisterAsSource = true;
		Sencer->RegisterForSense(UAISense_Sight::StaticClass());
	}
	//무브먼트
	{

	}
	//위젯
	{
		Widget->SetRelativeLocation(FVector(0, 0, 180));
	}
	//회전 설정
	{
		bUseControllerRotationYaw = true;
	}
	
	//데이터 테이블
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/GameBP/DataBase/StatTable.StatTable'"));
		if (Asset.Succeeded())
		{
			CS_Table = Asset.Object;
		}
	}
	//위젯 
	{
		static ConstructorHelpers::FClassFinder <UUserWidget> Asset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/GameBP/Widget/HP-Bar/Monster_HpBar.Monster_HpBar_C'"));
		if (Asset.Succeeded())
		{
			Widget->SetWidgetClass(Asset.Class);
		}
	}
}

void AFightPawnBase::BeginPlay()
{
	Super::BeginPlay();

	static const FString ContextString(TEXT("Character Stat Context"));
	FCharacterStats* Stats = CS_Table->FindRow<FCharacterStats>(FName(TEXT("Magician_1")), ContextString,true);

	if (Stats)
	{
		// 스탯 적용
		Health = FMath::RandRange(Stats->MinHealth , Stats->MaxHealth);
		Gage = FMath::RandRange(Stats->MinGage, Stats->MaxGage);;
		Damage = FMath::RandRange(Stats->MinDamage, Stats->MaxDamage);;
		// 기타 스탯 적용
	}

}



void AFightPawnBase::GetDamage(int32 Damages)
{
	if (Health <= 0)
	{
		return;  // 이미 사망한 상태면 더 이상 처리하지 않음
	}

	// 체력 감소
	Health -= Damages;
	FString Message = FString::Printf(TEXT("Character took %d damage, remaining health: %d"), Damages, Health);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Message);

	// 체력이 0 이하면 사망 처리
	if (Health <= 0)
	{
		//사망 애니메이션
		Death();
	}
}

void AFightPawnBase::Death()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "TESTSS");
}

void AFightPawnBase::Attack()
{
}

	