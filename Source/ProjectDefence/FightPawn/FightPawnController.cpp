// Fill out your copyright notice in the Description page of Project Settings.


#include "FightPawnController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


AFightPawnController::AFightPawnController()
{
	{
		static ConstructorHelpers::FObjectFinder<UBlackboardData> Asset(TEXT("BlackboardData'/Game/Behavior/FightMonster/LongRanged/LR_BB.LR_BB'"));
		if (Asset.Succeeded())
		{
			BBAsset = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UBehaviorTree> Asset(TEXT("BehaviorTree'/Game/Behavior/FightMonster/LongRanged/LR_BT.LR_BT'"));
		if (Asset.Succeeded())
		{
			BTAsset = Asset.Object;
		}
	}

	{
		Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	    SightConfig = NewObject<UAISenseConfig_Sight>(this, TEXT("SightConfig"));
		SightConfig->SightRadius = 1500;  // 반경 //변수 선언해서 공격 사거리 측정 
		SightConfig->LoseSightRadius = 1550.0f;  //인식이 사라지는 반경 // 뭔지 알아내기
		SightConfig->PeripheralVisionAngleDegrees = 180.0f;  // 주변 시야 각도 설정
		SightConfig->SetMaxAge(5.0f);  // 감지 정보의 최대 유지 시간 설정
		//SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;  // 마지막으로 보았던 위치에서 자동으로 성공 처리하는 범위
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;  // 적을 감지할지 여부
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;  // 아군을 감지할지 여부
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;  // 중립적인 대상을 감지할지 여부


		// 퍼셉션 컴포넌트에 시각 인식 설정 적용
		Perception->ConfigureSense(*SightConfig);
		// 인식 업데이트 이벤트에 대한 콜백 함수 연결
		Perception->OnPerceptionUpdated.AddDynamic(this, &AFightPawnController::OnPerceptionUpdated);
	}
}



void AFightPawnController::BeginPlay()
{
	Super::BeginPlay();

	//ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//if (PlayerCharacter)
	//{
	//	SetFocus(PlayerCharacter);
	//}



	// 시각적 인식을 위한 설정 객체 생성

}

void AFightPawnController::OnPossess(APawn* InPawn)
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

void AFightPawnController::Tick(float DeltaTime)
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

	for (AActor* Actor : Targets)
	{
		float Distance = FVector::Dist(this->GetPawn()->GetActorLocation(), Actor->GetActorLocation());
		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			Target = Actor;
		}

		if (Target)
		{
			Blackboard->SetValueAsObject("EnemyActor", Target);
			// 가장 가까운 액터에 대한 추가 처리 로직이 필요한 경우 여기에 구현
		}
	}

	//ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//float Distance = GetPawn()->GetDistanceTo(PlayerCharacter);

	//GetBlackboardComponent()->SetValueAsFloat(TEXT("Distance"), Distance);
	//AActor* FocusedActor = GetFocusActor();
}

void AFightPawnController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
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