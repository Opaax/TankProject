// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/TankMissile/TankBulletBase.h"

//UE
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATankBulletBase::ATankBulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(m_root);

	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_mesh->SetupAttachment(m_root);

	m_projectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
}

// Called when the game starts or when spawned
void ATankBulletBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankBulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

