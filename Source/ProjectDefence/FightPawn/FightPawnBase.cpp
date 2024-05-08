// Fill out your copyright notice in the Description page of Project Settings.


#include "FightPawnBase.h"
#include "StatDataTable.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Widget/FightMonsterHpBar.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AFightPawnBase::AFightPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	


	//생성
	{
		mSkel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainSkel"));
		mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MainCapsule"));
		Detection = CreateDefaultSubobject<USphereComponent>(TEXT("Detection"));
		Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
		Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	
	}
	//루트
	{
		RootComponent = mCapsule;
		mSkel->SetupAttachment(RootComponent);
		Widget->SetupAttachment(RootComponent);
		Detection->SetupAttachment(RootComponent);
	}
	//콜리전 설정
	{
		Detection->SetCollisionProfileName("Detection");
		Detection->SetSphereRadius(5000.0f);
		Detection->OnComponentBeginOverlap.AddDynamic(this, &AFightPawnBase::OnOverlapBegin);
	    Detection->OnComponentEndOverlap.AddDynamic(this, &AFightPawnBase::OnOverlapEnd);

		mCapsule->SetCollisionProfileName("PawnBase");
	}
	//위젯
	{
		Widget->SetRelativeLocation(FVector(0, 0, 175));
		Widget->SetWidgetSpace(EWidgetSpace::Screen);
		Widget->SetDrawSize(FVector2D(150.0f, 15.0f));
		Widget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

	if (!GetController()) return;
	MyController = Cast<AAIController>(GetController());

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

	UUserWidget* WidgetInstance = Widget->GetUserWidgetObject();
	if (WidgetInstance)
	{
		UFightMonsterHpBar* HpBar = Cast<UFightMonsterHpBar>(WidgetInstance);
		if (HpBar)
		{
			HpBar->FP= this;
		}
	}

}

void AFightPawnBase::Tick(float Time)
{
	Super::Tick(Time);

	//PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), Targets);

	float MinDistance = FLT_MAX;

	if (Targets.IsEmpty()) return;

	for (AActor* Actor : Targets)
	{
		auto* TargetCheck = Cast<AFightPawnBase>(Actor);

		if (TargetCheck->IsDying == true) continue;

		float Distances = FVector::Dist(GetActorLocation(), Actor->GetActorLocation());

		if (Distance < MinDistance)
		{
			MinDistance = Distances;
			Target = Cast<AFightPawnBase>(Actor);
		}

		if (Target)
		{
			if (!MyController) return;
			MyController->GetBlackboardComponent()->SetValueAsObject("EnemyActor", Target);
		}
	}

	if (Target)
	{
		if (Target->IsDying == true)
		{
			if (!MyController) return;
			MyController->GetBlackboardComponent()->SetValueAsObject("EnemyActor", nullptr);
		}
	}

	if (!Target) return;
	Distance = GetDistanceTo(Target);
	if (!MyController) return;
	MyController->GetBlackboardComponent()->SetValueAsFloat(TEXT("Distance"), Distance);
	//AActor* FocusedActor = GetFocusActor();
}



void AFightPawnBase::GetDamage(int32 Damages)
{
	if (Health <= 0)
	{
		return;  // 이미 사망한 상태면 더 이상 처리하지 않음
	}

	// 체력 감소
	Health -= Damages;
	FString Message = FString::Printf(TEXT("Character took %d damage, remaining health: %f"), Damages, Health);
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

void AFightPawnBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->Tags.Num() > 0)
		{
			if (Tags[0] == OtherActor->Tags[0])
			{
				//같으면
				return;
			}
			else if (Tags[0] != OtherActor->Tags[0])
			{

				Targets.Add(OtherActor);

				TArray<AActor*> FindEnemy;
				for (AActor* Actor : Targets)
				{
					if (!Actor) continue;

					if (Actor->Tags.Num() == 0 || Tags.Num() == 0) continue;

					if (Actor->Tags[0] == Tags[0]) continue;

					FindEnemy = Targets;
				}

				if (FindEnemy.IsEmpty())
				{
					Target = nullptr;
					MyController->GetBlackboardComponent()->SetValueAsObject("EnemyActor", Target);
					MyController->SetFocus(nullptr);
				}

			}

		}
	}
}

void AFightPawnBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		if (OtherActor->Tags.Num() > 0)
		{
			if (Tags[0] == OtherActor->Tags[0])
			{
				//같으면
				return;
			}
			else if (Tags[0] != OtherActor->Tags[0])
			{

				Targets.Remove(OtherActor);

				TArray<AActor*> FindEnemy;
				for (AActor* Actor : Targets)
				{
					if (!Actor) continue;

					if (Actor->Tags.Num() == 0 || Tags.Num() == 0) continue;

					if (Actor->Tags[0] == Tags[0]) continue;

					FindEnemy = Targets;
				}

				if (FindEnemy.IsEmpty())
				{
					Target = nullptr;
					MyController->GetBlackboardComponent()->SetValueAsObject("EnemyActor", Target);
					MyController->SetFocus(nullptr);
				}

			}

		}
	}
}

	