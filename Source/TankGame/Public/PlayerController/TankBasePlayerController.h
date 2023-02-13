// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankBasePlayerController.generated.h"

//Forward Tank
class ATankCharacter;

//Forward UE
class APawn;

/**
 * Base player controller for tank
 */
UCLASS()
class TANKGAME_API ATankBasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/////////////////////////// Props //////////////////////////

	UPROPERTY(BlueprintGetter = GetTankCharacter)
	ATankCharacter* m_character = nullptr;

	/////////////////////////// Func ///////////////////////////

	// Override

	virtual void BeginPlayingState() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	// Intern

	bool CheckCharacter();
	/// <summary>
	/// Check the character
	/// </summary>
	/// <param name="LogMessage">the message log if false</param>
	/// <returns>true if not nullptr</returns>
	bool CheckCharacter(FString LogMessage);

	// Input

	void MoveForward(float val);
	void MoveRight(float val);
	void RotateYaw(float val);
	void RotatePitch(float val);

	void PrimaryShoot();

	void BindGameInput();

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual ATankCharacter* GetTankCharacter() const;
};
