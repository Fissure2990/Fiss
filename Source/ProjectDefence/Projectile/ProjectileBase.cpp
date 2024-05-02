// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "../FightPawn/FightPawnBase.h"
// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(Sphere);
	Effect->SetupAttachment(Sphere);
	//발사체 속도
	{
		Movement->InitialSpeed = 500.0f;
		Movement->MaxSpeed = 0.0f;
		Movement->ProjectileGravityScale = 0.0f;
	}
	//콜리전
	{
		Sphere->SetSphereRadius(32.0f);
		Sphere->SetLineThickness(0.0f);

		Sphere->SetCollisionProfileName("Projectile");
		//Body->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//Body->SetCollisionObjectType(ECC_WorldDynamic);
		//Body->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
		//Body->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
		//Body->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
		//Body->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECollisionResponse::ECR_Ignore);

		Sphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnBeginOverlap);
	}

	{
		SetLifeSpan(30.0f);
	}

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileBase::SpawnSpike()
{
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!Master && !Damage) return;

	if (Other && OnlyOneDamage == false) 
	{
		// 태그가 있는지 확인
		if (Other->Tags.Num() > 0)
		{
			if (Other->Tags[0] == "Team")
			{

			}
			else if (Other->Tags[0] == "Enemy")
			{
				AFightPawnBase* Enemy = Cast<AFightPawnBase>(Other);
			    if (Enemy)
		     	{
				Enemy->GetDamage(Damage);
				OnlyOneDamage = true;
				Destroy();
				SpawnSpike();
			    }
			}
			else
			{
				return;
			}
		}

	}

}

