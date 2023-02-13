// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "PoolStructTable.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct TANKGAME_API FPoolStructTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ClassToPool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfInstances = 10;
};
