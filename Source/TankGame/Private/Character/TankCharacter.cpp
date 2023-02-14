// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TankCharacter.h"
#include "Camera/TankCameraController.h"
#include "TankGame/Public/PlayerController/TankBasePlayerController.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATankCharacter::ATankCharacter(const FObjectInitializer& ObjectInitializer):Super::ATankBaseCharacter(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_cameraController = CreateDefaultSubobject<UTankCameraController>(TEXT("Camera_Controller"));

	m_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera_Spring"));
	m_springArm->SetupAttachment(m_tankCanonPivot);

	m_cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_cameraComp->SetupAttachment(m_springArm);
}

void ATankCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ATankBasePlayerController* lTankController = Cast< ATankBasePlayerController>(GetController()))
	{
		m_cameraController->InitCameraController(lTankController);
	}
}

UTankCameraController* ATankCharacter::GetTankCameraController() const
{
	if (!IsValid(m_cameraController))
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to get tank character Camera Controller, but the controller is null"));

		return nullptr;
	}

	return m_cameraController;
}

UCameraComponent* ATankCharacter::GetTankCamera() const
{
	if (!IsValid(m_cameraComp))
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to get tank camera, but the camera is null"));

		return nullptr;
	}

	return m_cameraComp;
}

USpringArmComponent* ATankCharacter::GetTankSpringArm() const
{
	if (!IsValid(m_springArm))
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to get tank spring camera, but the srping is null"));

		return nullptr;
	}

	return m_springArm;
}

void ATankCharacter::PrimaryShoot()
{
	Super::PrimaryShoot();
}
void ATankCharacter::SecondaryShoot()
{
	Super::SecondaryShoot();
}

///////////////// EVENTS //////////////////
void ATankCharacter::OnPrimaryShoot_Implementation()
{
	m_cameraController->PlayShakePrimaryShoot();
}

void ATankCharacter::OnSecondaryShoot_Implementation()
{
}
