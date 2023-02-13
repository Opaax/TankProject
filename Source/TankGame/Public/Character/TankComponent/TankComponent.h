// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankComponent.generated.h"

//Forward UE
class USceneComponent;
class USkeletalMeshComponent;

//Forward Tank
class ATankBaseCharacter;
class ATankCharacter;

UCLASS()
class TANKGAME_API ATankComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankComponent();

protected:

	//////////////////// Construction ///////////////////

	UPROPERTY()
	TSet<ATankComponent*> m_children;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_rootComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* m_skMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName m_NameSocket;

	UPROPERTY()
	ATankBaseCharacter* m_ownerCharacter;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitComponent(ATankBaseCharacter* NewOwner);
	virtual void AttachToTank();

	virtual bool AddChild(ATankComponent* NewChild);
	virtual bool RemoveChild(ATankComponent* ChildToRemove);
	virtual TArray<ATankComponent*> GetChildren() const;
};
