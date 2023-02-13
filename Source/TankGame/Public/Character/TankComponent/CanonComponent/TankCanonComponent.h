// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TankComponent/TankComponent.h"
#include "TankCanonComponent.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankCanonComponent : public ATankComponent
{
	GENERATED_BODY()
	
public:

	virtual void AttachToTank() override;
};
