// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../TankBaseCharacter.h"
#include "TankCharacter.generated.h"

//Forward Tank
class UTankCameraController;

//Forward UE
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TANKGAME_API ATankCharacter : public ATankBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankCharacter(const FObjectInitializer& ObjectInitializer);

protected:

	////////////////////////////////// CAMERA //////////////////////////////////

	UPROPERTY(EditAnywhere,BlueprintGetter=GetTankCameraController, Category = "Tank/Camera")
	UTankCameraController* m_cameraController = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter = GetTankCamera, Category = "Tank/Camera")
	UCameraComponent* m_cameraComp = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter = GetTankSpringArm, Category = "Tank/Camera")
	USpringArmComponent* m_springArm = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	/*virtual void Tick(float DeltaTime) override;*/

	// Called to bind functionality to input
	/*virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;*/

	virtual void PrimaryShoot() override;
	virtual void SecondaryShoot() override;

	//////////////////// GETTERS /////////////////

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTankCameraController* GetTankCameraController() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCameraComponent* GetTankCamera() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	USpringArmComponent* GetTankSpringArm() const;

	//////////////// EVENTS /////////////////
	virtual void OnPrimaryShoot_Implementation() override;
	virtual void OnSecondaryShoot_Implementation() override;
};
