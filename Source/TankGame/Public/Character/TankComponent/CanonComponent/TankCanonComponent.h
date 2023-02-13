// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TankComponent/TankComponent.h"
#include "TankCanonComponent.generated.h"

//UE Forward
class USceneComponent;
/**
 * 
 */
UCLASS()
class TANKGAME_API ATankCanonComponent : public ATankComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere,Category = "Canon")
	USceneComponent* m_shootPosition = nullptr;
	
public:
	//Constructor
	ATankCanonComponent();

	virtual void AttachToTank() override;

	FVector GetShootLocation() const;
	FRotator GetShootRotation() const;
	FTransform GetShootTransform() const;
};
