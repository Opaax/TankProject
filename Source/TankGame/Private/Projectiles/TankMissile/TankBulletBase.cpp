// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/TankMissile/TankBulletBase.h"
#include "TankGame/Public/GameFramWork/GameModes/TankGameGameModeBase.h"
#include "TankGame/Public/GameFramWork/Managers/ObjectPoolManager.h"
#include "Tankgame/Public/FrameworkUtils/Components/TimerComponent.h"

//UE
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
	AddOwnedComponent(m_projectileComp);

	m_lifeTimer = CreateDefaultSubobject<UTimerComponent>(TEXT("Life_Timer"));
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

void ATankBulletBase::ActivateBullet()
{
	m_projectileComp->Velocity = GetActorForwardVector() * m_projectileComp->InitialSpeed;
	m_projectileComp->Activate();

	m_lifeTimer->Launch(m_bulletLifeTime, ETimerType::Dec, true);
	m_lifeTimer->OnTimerOver.AddDynamic(this, &ATankBulletBase::LifeTimer_OnTimerOver);
}

void ATankBulletBase::DesactivateBullet()
{
	m_projectileComp->Deactivate();
}

void ATankBulletBase::LifeTimer_OnTimerOver()
{
	DesactivateBullet();
	ReturnToPool();
	RemoveTimerBindFunction();
}

void ATankBulletBase::RemoveTimerBindFunction()
{
	m_lifeTimer->OnTimerOver.Clear();
}

//IPoolable
void ATankBulletBase::ReturnToPool()
{
	ATankGameGameModeBase* lGM = Cast<ATankGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (lGM == nullptr)
	{
		return;
	}

	UObjectPoolManager* lPoolManager = lGM->GetObjectPoolManager();

	if (lPoolManager == nullptr)
	{
		return;
	}

	lPoolManager->BackToPool(GetClass(), this);
}

void ATankBulletBase::DesactivatePoolObject()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void ATankBulletBase::ActivatePoolObject()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}
