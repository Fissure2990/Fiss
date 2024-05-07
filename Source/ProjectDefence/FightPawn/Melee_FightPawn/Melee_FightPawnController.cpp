// Fill out your copyright notice in the Description page of Project Settings.


#include "Melee_FightPawnController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMelee_FightPawnController::AMelee_FightPawnController()
{

	{
		static ConstructorHelpers::FObjectFinder<UBlackboardData> Asset(TEXT("/Script/AIModule.BlackboardData'/Game/GameBP/Behavior/FightMonster/Melee/Melee_BB.Melee_BB'"));
		if (Asset.Succeeded())
		{
			BBAsset = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UBehaviorTree> Asset(TEXT("/Script/AIModule.BehaviorTree'/Game/GameBP/Behavior/FightMonster/Melee/Melee_BT.Melee_BT'"));
		if (Asset.Succeeded())
		{
			BTAsset = Asset.Object;
		}
	}

	// 감지 기능
	{
		Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
		SightConfig = NewObject<UAISenseConfig_Sight>(this, TEXT("SightConfig"));
		SightConfig->SightRadius = 5000;  // 반경 //변수 선언해서 공격 사거리 측정 
		SightConfig->LoseSightRadius = 5500.0f;  //인식이 사라지는 반경 // 뭔지 알아내기
		SightConfig->PeripheralVisionAngleDegrees = 180.0f;  // 주변 시야 각도 설정
		SightConfig->SetMaxAge(5.0f);  // 감지 정보의 최대 유지 시간 설정
		//SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;  // 마지막으로 보았던 위치에서 자동으로 성공 처리하는 범위
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;  // 적을 감지할지 여부
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;  // 아군을 감지할지 여부
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;  // 중립적인 대상을 감지할지 여부


		// 퍼셉션 컴포넌트에 시각 인식 설정 적용
		Perception->ConfigureSense(*SightConfig);
		// 인식 업데이트 이벤트에 대한 콜백 함수 연결
		Perception->OnPerceptionUpdated.AddDynamic(this, &AMelee_FightPawnController::OnPerceptionUpdated);
	}
}

void AMelee_FightPawnController::BeginPlay()
{
	Super::BeginPlay();
	//SightConfig->SightRadius = 5000;  // 반경 //변수 선언해서 공격 사거리 측정 
	//SightConfig->LoseSightRadius = 5500.0f;  //인식이 사라지는 반경 // 뭔지 알아내기
}

void AMelee_FightPawnController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BBAsset)
	{

		UBlackboardComponent* BBref = Blackboard;
		if (UseBlackboard(BBAsset, BBref))
		{
			RunBehaviorTree(BTAsset);
		}
	}
}

void AMelee_FightPawnController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	if (SightConfig)
	{
		float SightRadius = SightConfig->SightRadius;
		FVector Location = GetPawn()->GetActorLocation();

		// 시각 범위를 디버깅 원으로 그립니다.
		DrawDebugSphere(GetWorld(), Location, SightRadius, 32, FColor::Green, false, -1.0f, 0, 1.0f);
	}

	//PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), Targets);

	float MinDistance = FLT_MAX;

	if (Targets.IsEmpty()) return;

	for (AActor* Actor : Targets)
	{
		if (!Actor || !GetPawn()) continue;

		if (Actor->Tags.Num() == 0 || GetPawn()->Tags.Num() == 0) continue;


		if (Actor->Tags[0] == GetPawn()->Tags[0]) continue;

		auto* TargetCheck = Cast<AFightPawnBase>(Actor);

		if (TargetCheck->IsDying == true) continue;

		float Distances = FVector::Dist(this->GetPawn()->GetActorLocation(), Actor->GetActorLocation());

		if (Distance < MinDistance)
		{
			MinDistance = Distances;
			Target = Cast<AFightPawnBase>(Actor);
		}

		if (Target)
		{
			Blackboard->SetValueAsObject("EnemyActor", Target);
		}
	}

	if (Target)
	{
		if (Target->IsDying == true)
		{
			Blackboard->SetValueAsObject("EnemyActor", nullptr);
		}
	}

	if (!Target) return;
	//SetFocus(Target);
	Distance = GetPawn()->GetDistanceTo(Target);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("Distance"), Distance);
	//AActor* FocusedActor = GetFocusActor();
}

void AMelee_FightPawnController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> CurActor;
	PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), CurActor);
	Targets = CurActor;
	if (Targets.IsEmpty())
	{
		Target = nullptr;
		Blackboard->SetValueAsObject("EnemyActor", Target);
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, "Empty!");
		SetFocus(nullptr);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, "enemy");
}
