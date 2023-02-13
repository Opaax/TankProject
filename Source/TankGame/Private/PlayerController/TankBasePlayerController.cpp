// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/TankBasePlayerController.h"
#include "Character/TankCharacter.h"

#include "GameFramework/Pawn.h"

// Overrrides 

void ATankBasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	BindGameInput();

	UE_LOG(LogTemp, Error, TEXT("Tank player controller Beginplay End"));
}

void ATankBasePlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();

	m_character = Cast<ATankCharacter>(GetPawn());

	CheckCharacter();
}

void ATankBasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!CheckCharacter("Checking the Character on Player controller on the OnPossess function. Missing Character as ATankCharacter"))
		return;
	else
		UE_LOG(LogTemp,Display,TEXT("PlayerController, OnPossess goes right"))

	m_character->InitTank();
}

// Protected PC

bool ATankBasePlayerController::CheckCharacter()
{
	if (m_character == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Tank player controller check his character and didn't find it"));
	}

	return m_character == nullptr ? false : true;
}

bool ATankBasePlayerController::CheckCharacter(FString LogMessage)
{
	if (m_character == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *LogMessage);
	}

	return m_character == nullptr ? false : true;
}

//Inputs
void ATankBasePlayerController::MoveForward(float val)
{
	if (!IsValid(m_character))
		return;

	if (val != 0)
	{
		m_character->MoveForward(val);
	}
}

void ATankBasePlayerController::MoveRight(float val)
{
	if (!IsValid(m_character))
		return;

	if (val != 0)
	{
		m_character->MoveRight(val);
	}
}

void ATankBasePlayerController::RotateYaw(float val)
{
	//UE_LOG(LogTemp, Error, TEXT("Tank player controller MoveRight"));

	if (!IsValid(m_character))
		return;

	if (val != 0)
	{
		m_character->RotateTopPivotYaw(val);
	}
}

void ATankBasePlayerController::RotatePitch(float val)
{
	//UE_LOG(LogTemp, Error, TEXT("Tank player controller MoveRight"));

	if (!IsValid(m_character))
		return;

	if (val != 0)
	{
		m_character->RotateTopPivotPitch(val);
	}
}

void ATankBasePlayerController::PrimaryShoot()
{
	if (!IsValid(m_character))
		return;

	m_character->PrimaryShoot();
}

void ATankBasePlayerController::BindGameInput()
{
	SetupInputComponent();

	UE_LOG(LogTemp, Display, TEXT("Tank player controller BindInput"));

	InputComponent->BindAxis("MoveForward", this, &ATankBasePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATankBasePlayerController::MoveRight);
	InputComponent->BindAxis("YawAxis", this, &ATankBasePlayerController::RotateYaw);
	InputComponent->BindAxis("PitchAxis", this, &ATankBasePlayerController::RotatePitch);

	InputComponent->BindAction("PrimaryShoot", EInputEvent::IE_Pressed, this, &ATankBasePlayerController::PrimaryShoot);

	//// Bind jump events
	//InputComponent->BindAction("Jump", IE_Pressed, this, &ADABPlayerController::Jump);
	//InputComponent->BindAction("Jump", IE_Released, this, &ADABPlayerController::StopJump);

	//InputComponent->BindAction("Dash", IE_Pressed, this, &ADABPlayerController::Dash);

	//// Bind fire event
	//InputComponent->BindAction("Fire", IE_Pressed, this, &ADABPlayerController::PressShootWeapon);
	//InputComponent->BindAction("Fire", IE_Released, this, &ADABPlayerController::ReleaseShootWeapon);
	//// Bind fire event
	//InputComponent->BindAction("TokenFire", IE_Pressed, this, &ADABPlayerController::PressShootToken);
	//InputComponent->BindAction("TokenFire", IE_Released, this, &ADABPlayerController::ReleaseShootToken);

	//InputComponent->BindAction("Pause", IE_Pressed, this, &ADABPlayerController::OpenPauseMenu);

	//// Bind movement events
	//
	//InputComponent->BindAxis("MoveUp", this, &ADABPlayerController::MoveUp);

	//// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	//// "turn" handles devices that provide an absolute delta, such as a mouse.
	//// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//InputComponent->BindAxis("Turn", this, &ADABPlayerController::Turn);
	//InputComponent->BindAxis("TurnRate", this, &ADABPlayerController::TurnAtRate);
	//InputComponent->BindAxis("LookUp", this, &ADABPlayerController::LookUp);
	//InputComponent->BindAxis("LookUpRate", this, &ADABPlayerController::LookUpAtRate);
}

//////////////////////////// PUBLIC ///////////////////////////////

ATankCharacter* ATankBasePlayerController::GetTankCharacter() const
{
	return m_character;
}
