// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "FightPawnBase.generated.h"

UCLASS()
class PROJECTDEFENCE_API AFightPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFightPawnBase();
	virtual void BeginPlay();
	virtual void Tick(float Time);

public:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mSkel;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	UDataTable* CS_Table;
	
	//스탯
		UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		float Health = 0;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Gage = 0;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)	
		int32 Armor = 0;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Damage = 0;
	//데미지
		void GetDamage(int32 Damages);
		virtual void Death();
		virtual void Attack();
protected:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
	USphereComponent* Detection;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(EditAnywhere)
	TArray<AActor*> Targets;




	UPROPERTY(EditAnywhere)
	float Distance;

	UPROPERTY()
	AAIController* MyController;
public:
	bool IsDying = false;
	UPROPERTY(EditAnywhere)
	UWidgetComponent* Widget;

	UPROPERTY(EditAnywhere)
	AFightPawnBase* Target;

};
