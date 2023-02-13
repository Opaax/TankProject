// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TankCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API UTankCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UTankCharacterMovementComponent();

	void virtual PerformMovement(float DeltaTime) override;
};
