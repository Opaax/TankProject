// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TankCameraController.generated.h"

//TANK
class ATankBasePlayerController;

//UE
class UCameraShakeBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankCameraController : public USceneComponent
{
	GENERATED_BODY()

protected:

	ATankBasePlayerController* m_playerTankController = nullptr;

	UPROPERTY(EditAnywhere, Category = "Tank/Shoot")
	TSubclassOf<UCameraShakeBase> m_primaryShakeClass = nullptr;
	UPROPERTY(EditAnywhere, Category = "Tank/Shoot")
	TSubclassOf<UCameraShakeBase> m_secondaryShakeClass = nullptr;

public:	
	// Sets default values for this component's properties
	UTankCameraController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitCameraController(ATankBasePlayerController* PlayerControllerTank);

	virtual void PlayShakePrimaryShoot();
	virtual void PlayShakeSecondaryShoot();
		
};
