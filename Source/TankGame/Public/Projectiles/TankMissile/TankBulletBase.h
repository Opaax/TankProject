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
	
	UPROPERTY(EditAnywhere, category = "Timer/Settings")
	float m_bulletLifeTime = 5.0;
	
public:	
	// Sets default values for this actor's properties
	ATankBulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void LifeTimer_OnTimerOver();
	UFUNCTION()
	void RemoveTimerBindFunction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ActivateBullet();
	virtual void DesactivateBullet();

	//IPoolable
	virtual void ReturnToPool() override;
	virtual void DesactivatePoolObject() override;
	virtual void ActivatePoolObject() override;
};
