// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankBulletBase.generated.h"

//UE
class UStaticMeshComponent;
class USceneComponent;
class UProjectileMovementComponent;

UCLASS()
class TANKGAME_API ATankBulletBase : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Visual")
	USceneComponent* m_root = nullptr;

	UPROPERTY(EditAnywhere, Category = "Visual")
	UStaticMeshComponent* m_mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UProjectileMovementComponent* m_projectileComp = nullptr;
	
public:	
	// Sets default values for this actor's properties
	ATankBulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
