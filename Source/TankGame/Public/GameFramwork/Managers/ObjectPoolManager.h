// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPoolManager.generated.h"

//UE
class UDataTable;
class AActor;

/**
 * 
 */
UCLASS()
class TANKGAME_API UObjectPoolManager : public UObject
{
	GENERATED_BODY()
	
private:

	TMap<TSubclassOf<AActor>, TArray<AActor*>>* m_poolContainer;

	UPROPERTY(BlueprintGetter = GetOwner, VisibleDefaultsOnly)
	AActor* m_owner = nullptr;

protected:
	UFUNCTION()
	/// <summary>
	/// Init the pool in container
	/// </summary>
	/// <param name="Class">Pool Class</param>
	/// <param name="NumberOfInstances">number of poolable</param>
	void InitPool(TSubclassOf<AActor> Class, float NumberOfInstances);

	UFUNCTION()
	/// <summary>
	/// Add poolable in giving keyclass pool
	/// </summary>
	/// <param name="KeyClass">the key to find pool in container</param>
	/// <param name="Poolable">current poolable to add</param>
	void AddOnPool(TSubclassOf<AActor> KeyClass, AActor* Poolable);

	UFUNCTION()
	/// <summary>
	/// Create a new pool in the container
	/// </summary>
	/// <param name="KeyClass">The pool key to create</param>
	void CreatePool(TSubclassOf<AActor> KeyClass);

	UFUNCTION()
	/// <summary>
	/// 
	/// </summary>
	/// <param name="KeyClass"></param>
	/// <param name="NumberOfInstance"></param>
	void SpawnRange(TSubclassOf<AActor> KeyClass, float NumberOfInstance);

public:
	//construct
	UObjectPoolManager();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// 
	/// </summary>
	/// <param name="NewOwner">the new owner</param>
	/// <param name="PoolTable">data for pool to create</param>
	void InitObjectPoolManager(AActor* NewOwner, UDataTable* PoolTable);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	/// <summary>
	/// Get the current owner of this manager
	/// </summary>
	/// <returns>the actor that own this manager</returns>
	AActor* GetOwner() const;

	template<class T>
	FORCEINLINE typename TEnableIf<TIsDerivedFrom<T, AActor>::IsDerived, T*>::Type
		GetPoolObject()
	{
		if (TArray<AActor*>* lPoolList = m_poolContainer->Find(T::StaticClass()))
		{
			if (lPoolList->IsEmpty())
			{
				SpawnRange(T::StaticClass(), 10);
			}

			T* lReturnableOBJ = (T*)lPoolList->Pop();
			return lReturnableOBJ;
		}

		return nullptr;
	}
};
