// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramwork/Managers/ObjectPoolManager.h"

//UE
#include "Engine/DataTable.h"
#include "Containers/Array.h"
#include "GameFramework/Actor.h"

//Tank
#include "TankGame/Public/Data/Tables/PoolStructTable.h"
#include "TankGame/Public/FrameworkUtils/Interfaces/PoolableInterface.h"

UObjectPoolManager::UObjectPoolManager()
{
	m_poolContainer = new TMap<TSubclassOf<AActor>, TArray<AActor*>>();
}

void UObjectPoolManager::InitObjectPoolManager(AActor* NewOwner, UDataTable* PoolTable)
{
	if (!IsValid(NewOwner))
	{
		UE_LOG(LogTemp, Error, TEXT("The pool new owner is not valid"));
	}

	m_owner = NewOwner;

	if (!IsValid(PoolTable))
	{
		UE_LOG(LogTemp, Error, TEXT("The pool table is not valid"));
	}

	TArray<FName> DataTableRowsName;
	FPoolStructTable* lData;

	DataTableRowsName = PoolTable->GetRowNames();

	for (FName RowName : DataTableRowsName)
	{
		lData = PoolTable->FindRow<FPoolStructTable>(RowName, TEXT(""), true);

		if (lData != nullptr)
		{
			InitPool(lData->ClassToPool, lData->NumberOfInstances);
		}
	}
}

void UObjectPoolManager::InitPool(TSubclassOf<AActor> Class, float NumberOfInstances)
{
	SpawnRange(Class, NumberOfInstances);
}

void UObjectPoolManager::SpawnRange(TSubclassOf<AActor> KeyClass, float NumberOfInstances)
{
	UWorld* lWorld = m_owner->GetWorld();

	// Its cost little bit of perf, indeed in our case the owner is own by the world, the world can't be NULL
	//But in different case could be usefull
	if (!IsValid(lWorld))
	{
		UE_LOG(LogTemp, Error, TEXT("The world is not valid"));
		return;
	}

	FTransform lTransform = m_owner->GetTransform();
	FActorSpawnParameters lSpawnInfo;

	lSpawnInfo.Owner = m_owner;
	lSpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int i = 0; i < NumberOfInstances; i++)
	{
		AActor* lNewActor = lWorld->SpawnActor<AActor>(KeyClass, lTransform, lSpawnInfo);

		AddOnPool(KeyClass, lNewActor);
	}
}

void UObjectPoolManager::AddOnPool(TSubclassOf<AActor> KeyClass, AActor* Poolable)
{
	if (TArray<AActor*>* lPoolList = m_poolContainer->Find(KeyClass))
	{
		lPoolList->Add(Poolable);
	}
	else
	{
		CreatePool(KeyClass);
		AddOnPool(KeyClass, Poolable);
	}
}

void UObjectPoolManager::CreatePool(TSubclassOf<AActor> KeyClass)
{
	m_poolContainer->Add(KeyClass, TArray<AActor*>());
}

AActor* UObjectPoolManager::GetOwner() const
{
	if (!IsValid(m_owner))
	{
		UE_LOG(LogTemp, Error, TEXT("The Pool manager owner is not valid"));
		return nullptr;
	}

	return m_owner;
}

bool UObjectPoolManager::BackToPool(TSubclassOf<AActor> KeyClass, AActor* Poolable)
{
	if (Poolable->GetClass()->ImplementsInterface(UPoolableInterface::StaticClass()))
	{
		AddOnPool(KeyClass, Poolable);

		return true;
	}
	return false;
}
