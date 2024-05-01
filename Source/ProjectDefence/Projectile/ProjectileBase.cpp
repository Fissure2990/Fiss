// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

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
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "testst");

}

