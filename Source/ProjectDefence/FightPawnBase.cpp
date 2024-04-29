// Fill out your copyright notice in the Description page of Project Settings.


#include "FightPawnBase.h"

// Sets default values
AFightPawnBase::AFightPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mSkel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainSkel"));
	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MainCapsule"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	RootComponent = mCapsule;
	mSkel->SetupAttachment(mCapsule);


}

// Called when the game starts or when spawned
void AFightPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFightPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFightPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

