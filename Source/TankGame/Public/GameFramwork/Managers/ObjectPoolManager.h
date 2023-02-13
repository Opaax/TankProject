// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPoolManager.generated.h"

//UE
class UDataTable;
class AActor;
class UPoolableInterface;

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

	UFUNCTION(BlueprintCallable)
	bool BackToPool(TSubclassOf<AActor> KeyClass, AActor* Poolable);

	template<class T>
	FORCEINLINE typename TEnableIf<TIsDerivedFrom<T, AActor>::IsDerived, T*>::Type
		GetPoolObject()
	{
		if (m_poolContainer->Num() > 0)
		{
			//lPool should be TMap<TSubclassOf<AActor>, TArray<AActor*>>*
			for (auto& lPool : *m_poolContainer)
			{
				if (lPool.Key.GetDefaultObject()->IsA(T::StaticClass()))
				{
					if (lPool.Value.IsEmpty())
					{
						SpawnRange(lPool.Key.Get(), 10);
					}

					T* lReturnableOBJ = (T*)lPool.Value.Pop();
					return lReturnableOBJ;
				}
			}

			return nullptr;
		}

		UE_LOG(LogTemp, Error, TEXT("Pool not found"));

		return nullptr;
	}
};
