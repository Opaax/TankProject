// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBaseCharacter.h"

#include "Character/MovementComponent/TankCharacterMovementComponent.h"
#include "Character/TankComponent/TankComponent.h"
#include "Character/TankComponent/HeadComponent/TankHeadComponent.h"
#include "Character/TankComponent/BodyComponent/TankBodyComponent.h"
#include "Character/TankComponent/CanonComponent/TankCanonComponent.h"

#include "TankGame/Public/Projectiles/TankMissile/TankBulletBase.h"

#include "TankGame/Public/GameFramwork/GameModes/TankGameGameModeBase.h"
#include "TankGame/Public/GameFramwork/Managers/ObjectPoolManager.h"

//UE LIB
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"

#include "Misc/DefaultValueHelper.h"

#include "UObject/UObjectGlobals.h"

// Sets default values
ATankBaseCharacter::ATankBaseCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UTankCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))

{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_tankMovementComponent = Cast<UTankCharacterMovementComponent>(GetCharacterMovement());

	ConstructTankBodyPivot();
	ConstructTankHeadPivot();
	ConstructTankCanonPivot();
}

// Called when the game starts or when spawned
void ATankBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	HideSkPreview();
}

// Called every frame
void ATankBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

////////////////// Protected ////////////////////

void ATankBaseCharacter::ConstructTankBodyPivot()
{
	m_tankBodyPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Tank_Body"));
	m_tankBodyPivot->SetupAttachment(RootComponent);

	m_bodySkPreview = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TankBody_SK_Preview"));
	m_bodySkPreview->SetupAttachment(m_tankBodyPivot);
}

void ATankBaseCharacter::ConstructTankHeadPivot()
{
	m_tankHeadPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Tank_Head"));
	m_tankHeadPivot->SetupAttachment(RootComponent);

	m_headSkPreview = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TankHead_SK_Preview"));
	m_headSkPreview->SetupAttachment(m_tankHeadPivot);
}

void ATankBaseCharacter::ConstructTankCanonPivot()
{
	m_tankCanonPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Tank_Canon"));
	m_tankCanonPivot->SetupAttachment(m_tankHeadPivot);

	m_canonSkPreview = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TankCanon_SK_Preview"));
	m_canonSkPreview->SetupAttachment(m_tankCanonPivot);
}

void ATankBaseCharacter::HideSkPreview() const
{
	if (IsValid(m_bodySkPreview))
	{
		m_bodySkPreview->SetVisibility(false, true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Character, m_bodySKPreview is not valid"));
	}

	if (IsValid(m_headSkPreview))
	{
		m_headSkPreview->SetVisibility(false, true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Character, m_headSkPreview is not valid"));
	}

	if (IsValid(m_canonSkPreview))
	{
		m_canonSkPreview->SetVisibility(false, true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Character, m_canonSkPreview is not valid"));
	}

	/*IsValid(m_bodySkPreview) ? m_bodySkPreview->SetHiddenInGame(false, true) : UE_LOG(LogTemp, Error, TEXT("Character, m_bodySKPreview is not valid"));
	IsValid(m_headSkPreview) ? m_headSkPreview->SetHiddenInGame(false, true) : UE_LOG(LogTemp, Error, TEXT("Character, m_headSkPreview is not valid"));
	IsValid(m_canonSkPreview) ? m_canonSkPreview->SetHiddenInGame(false, true) : UE_LOG(LogTemp, Error, TEXT("Character, m_canonSkPreview is not valid"));*/
}

////////////////// Public ///////////////////////

void ATankBaseCharacter::MoveForward(const float inputVal)
{
	if (GetCharacterMovement() == nullptr)
		return;

	FRotator lRot = GetControlRotation();

	lRot.Pitch = 0;
	lRot.Roll = 0;

	ApplyNewMovementDirection(UKismetMathLibrary::GetForwardVector(lRot), inputVal);
}

void ATankBaseCharacter::MoveRight(const float inputVal)
{
	if (GetCharacterMovement() == nullptr)
		return;

	ApplyNewRotation(inputVal);
}

void ATankBaseCharacter::RotateTopPivotYaw(const float val)
{
	ApplyNewTopPivotRotationYaw(val);
}

void ATankBaseCharacter::RotateTopPivotPitch(const float val)
{
	ApplyNewTopPivotRotationPitch(val);
}

void ATankBaseCharacter::ApplyNewMovementDirection(const FVector direction, const float scale)
{
	AddMovementInput(direction, scale);
}

void ATankBaseCharacter::ApplyNewRotation(const float scale)
{
	AddControllerYawInput(scale);
}

void ATankBaseCharacter::ApplyNewTopPivotRotationYaw(const float val)
{
	m_tankHeadPivot->AddLocalRotation(FRotator(0, val, 0));
	//m_tankCanonPivot->AddLocalRotation(FRotator(0, val, 0));
}

void ATankBaseCharacter::ApplyNewTopPivotRotationPitch(const float val)
{
	if(CheckPitchCanonRotation(val))
		m_tankCanonPivot->AddLocalRotation(FRotator(val, 0, 0));
}

bool ATankBaseCharacter::CheckPitchCanonRotation(float NextAddValue) const
{
	FRotator lCurrentRotation = m_tankCanonPivot->GetRelativeRotation();

	if (NextAddValue < 0)
	{
		if (lCurrentRotation.Pitch > m_minPitchCanonRotation)
			return true;
	}
	else if (NextAddValue > 0)
	{
		if (lCurrentRotation.Pitch < m_maxPitchCanonRotation)
			return true;
	}

	return false;
}

template<class T>
typename TEnableIf<TIsDerivedFrom<T, ATankComponent>::IsDerived, T*>::Type
ATankBaseCharacter::SpawnTankComponent(TSubclassOf<T> TankComponentClass, const FTransform& Transform, const FActorSpawnParameters& SpawnParams)
{
	UWorld* lWorld = GetWorld();

	if (lWorld != nullptr)
	{
		return lWorld->SpawnActor<T>(TankComponentClass, Transform, SpawnParams);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("You are looking for spawn ATankComponent, but for some how world is nullptr"));
		return nullptr;
	}
}

void ATankBaseCharacter::PrimaryShoot()
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
	
	ATankBulletBase* lBullet = lPoolManager->GetPoolObject<ATankBulletBase>();

	if (!IsValid(lBullet))
	{
		UE_LOG(LogTemp, Error, TEXT("Primary shoot lActor is not valid"));
		return;
	}

	FTransform lTrans = m_tankCanon->GetShootTransform();

	UKismetMathLibrary::InvertTransform(lTrans);

	lBullet->SetActorRelativeTransform(lTrans);
	//lBullet->SetActorLocationAndRotation(lTrans.GetLocation(), lTrans.GetRotation());
	//lBullet->SetActorRotation(m_tankHeadPivot->GetComponentTransform().GetRotation());
	//lBullet->ActivateBullet();
}

void ATankBaseCharacter::InitTank()
{
	if (bIsTankInit) return;
	if (!IsValid(m_tankHeadComponentClass))
	{
		UE_LOG(LogTemp, Error, TEXT("Init Tank in Character, no class selected for 'm_topTankClass'"));

		return;
	}

	m_tankHead = SpawnHeadComponent(m_tankHeadComponentClass);
	m_tankCanon = SpawnCanonComponent(m_tankCanonComponentClass);
	m_tankBody = SpawnBodyComponent(m_tankBodyComponentClass);

	if (!IsValid(m_tankHead) || !IsValid(m_tankCanon) || !IsValid(m_tankBody))
	{
		UE_LOG(LogTemp, Error, TEXT("Init Tank in Character, but one of its component is not valide. Something went wrong while spawning object"));

		return;
	}

	m_tankHead->InitComponent(this);
	m_tankCanon->InitComponent(this);
	m_tankBody->InitComponent(this);

	bIsTankInit = true;
}

ATankBodyComponent* ATankBaseCharacter::SpawnBodyComponent(TSubclassOf<ATankBodyComponent> BodyClass)
{
	return SpawnTankComponent<ATankBodyComponent>(BodyClass, FTransform(), GetDefaultSpawnParams());
}

ATankHeadComponent* ATankBaseCharacter::SpawnHeadComponent(TSubclassOf<ATankHeadComponent> HeadClass)
{
	return SpawnTankComponent<ATankHeadComponent>(HeadClass, FTransform(), GetDefaultSpawnParams());
}

ATankCanonComponent* ATankBaseCharacter::SpawnCanonComponent(TSubclassOf<ATankCanonComponent> CanonClass)
{
	return SpawnTankComponent<ATankCanonComponent>(CanonClass, FTransform(), GetDefaultSpawnParams());
}

bool ATankBaseCharacter::CheckTankHeadComponent() const
{
	return GetHeadPivot() != nullptr ? true : false;
}

/////////////////////// Getters /////////////////////

USceneComponent* ATankBaseCharacter::GetHeadPivot() const
{
	return m_tankHeadPivot;
}

USceneComponent* ATankBaseCharacter::GetBodyPivot() const
{
	return m_tankBodyPivot;
}

USceneComponent* ATankBaseCharacter::GetCanonPivot() const
{
	return m_tankCanonPivot;
}

FActorSpawnParameters ATankBaseCharacter::GetDefaultSpawnParams()
{
	FActorSpawnParameters lSpawnInfo;
	lSpawnInfo.Owner = this;
	lSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return lSpawnInfo;
}
