// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameGameModeBase.generated.h"

//Tank
class UObjectPoolManager;

//UE
class UDataTable;

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	/// <summary>
	/// Pool Manager
	/// </summary>
	UPROPERTY(BlueprintGetter = GetObjectPoolManager)
	UObjectPoolManager* m_objectPoolManager;

	virtual void BeginPlay() override;

	UFUNCTION()
	void CreateObjectPoolManager();

protected:

	UPROPERTY(EditDefaultsOnly,Category = "Tank/Pool")
	UDataTable* m_poolTable;

public:

	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UObjectPoolManager* GetObjectPoolManager() const;
};
