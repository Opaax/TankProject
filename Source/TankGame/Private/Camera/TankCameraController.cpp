// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/TankCameraController.h"
#include "TankGame/Public/PlayerController/TankBasePlayerController.h"

#include "Camera/CameraShakeBase.h"

// Sets default values for this component's properties
UTankCameraController::UTankCameraController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankCameraController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankCameraController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankCameraController::InitCameraController(ATankBasePlayerController* PlayerControllerTank)
{
	m_playerTankController = PlayerControllerTank;
}

void UTankCameraController::PlayShakePrimaryShoot()
{
	if (m_primaryShakeClass)
	{
		m_playerTankController->ClientPlayCameraShake(m_primaryShakeClass);
	}
}

void UTankCameraController::PlayShakeSecondaryShoot()
{
	
}
