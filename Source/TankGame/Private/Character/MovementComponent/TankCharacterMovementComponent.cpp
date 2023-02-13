// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MovementComponent/TankCharacterMovementComponent.h"

#include "Character/TankCharacter.h"

UTankCharacterMovementComponent::UTankCharacterMovementComponent()
{
    SetMovementMode(MOVE_Walking);
}

void UTankCharacterMovementComponent::PerformMovement(float DeltaTime)
{
    Super::PerformMovement(DeltaTime);
}
