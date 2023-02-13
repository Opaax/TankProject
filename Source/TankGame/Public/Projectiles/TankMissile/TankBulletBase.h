// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankGame/Public/FrameworkUtils/Interfaces/PoolableInterface.h"
#include "TankBulletBase.generated.h"

//UE
class UStaticMeshComponent;
class USceneComponent;
class UProjectileMovementComponent;

//Tank
class UTimerComponent;

UCLASS()
class TANKGAME_API ATankBulletBase : public AActor, public IPoolableInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Visual")
	USceneComponent* m_root = nullptr;

	UPROPERTY(EditAnywhere, Category = "Visual")
	UStaticMeshComponent* m_mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UProjectileMovementComponent* m_projectileComp = nullptr;

	UPROPERTY(EditAnywhere, category = "Timer")
	UTimerComponent* m_lifeTimer = nullptr;

	UFUNCTION()
	void LifeTimer_OnTimerOver();
	UFUNCTION()
	void RemoveTimerBindFunction();
	
public:	
	// Sets default values for this actor's properties
	ATankBulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ActivateBullet();

	//IPoolable
	virtual void ReturnToPool() override;
};
