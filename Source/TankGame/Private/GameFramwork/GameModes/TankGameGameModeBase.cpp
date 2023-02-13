// Copyright Epic Games, Inc. All Rights Reserved.


#include "../../../Public/GameFramwork/GameModes/TankGameGameModeBase.h"
#include "GameFramwork/Managers/ObjectPoolManager.h"


void ATankGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CreateObjectPoolManager();
}

void ATankGameGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	FTransform lTransform;

	RestartPlayerAtTransform(NewPlayer, lTransform);
}

void ATankGameGameModeBase::CreateObjectPoolManager()
{
	if (m_objectPoolManager != nullptr) return;

	m_objectPoolManager = NewObject<UObjectPoolManager>();
	m_objectPoolManager->InitObjectPoolManager(this,m_poolTable);
}

////////////// Getter ////////////////////

/// <summary>
/// Get the pool manager
/// </summary>
/// <returns>nullptr if manager is not created</returns>
UObjectPoolManager* ATankGameGameModeBase::GetObjectPoolManager() const
{
	if (m_objectPoolManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Looking to get Object pool manager, but it's null"));

		return nullptr;
	}

	return m_objectPoolManager;
}