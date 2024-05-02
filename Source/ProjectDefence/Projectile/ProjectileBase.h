// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "ProjectileBase.generated.h"

UCLASS()
class PROJECTDEFENCE_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	UNiagaraComponent* Effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	UProjectileMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere);
	int32 Damage;

	UPROPERTY(VisibleAnywhere)
	AActor* Master;

	bool OnlyOneDamage = false;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpawnSpike();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
