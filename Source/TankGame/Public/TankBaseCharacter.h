// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/ObjectMacros.h"
#include "TankBaseCharacter.generated.h"

//Forward UE
class UStaticMeshComponent;
class USkeletalMeshComponent;
class USceneComponent;

//Forward Tank
class UTankCharacterMovementComponent;
class ATankComponent;
class ATankHeadComponent;
class ATankBodyComponent;
class ATankCanonComponent;

UCLASS()
class TANKGAME_API ATankBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankBaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:

	///////////////////////////// Construction //////////////////////////////

	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter = GetBodyPivot, Category = "Tank/Scene/Pivot")
	USceneComponent* m_tankBodyPivot;
	UPROPERTY(VisibleDefaultsOnly,BlueprintGetter = GetHeadPivot, Category = "Tank/Scene/Pivot")
	USceneComponent* m_tankHeadPivot;
	UPROPERTY(VisibleDefaultsOnly, BlueprintGetter = GetCanonPivot, Category = "Tank/Scene/Pivot")
	USceneComponent* m_tankCanonPivot;

	UPROPERTY(VisibleDefaultsOnly, Category = "Tank/Preview")
	USkeletalMeshComponent* m_bodySkPreview = nullptr;
	UPROPERTY(VisibleDefaultsOnly, Category = "Tank/Preview")
	USkeletalMeshComponent* m_headSkPreview = nullptr;
	UPROPERTY(VisibleDefaultsOnly, Category = "Tank/Preview")
	USkeletalMeshComponent* m_canonSkPreview = nullptr;

	UPROPERTY(EditAnywhere, Category = "Tank/Component")
	TSubclassOf<ATankBodyComponent> m_tankBodyComponentClass;
	UPROPERTY(BlueprintReadWrite, Category = "Tank/Component")
	ATankBodyComponent* m_tankBody = nullptr;

	UPROPERTY(EditAnywhere, Category = "Tank/Component")
	TSubclassOf<ATankHeadComponent> m_tankHeadComponentClass;
	UPROPERTY(BlueprintReadWrite, Category = "Tank/Component")
	ATankHeadComponent* m_tankHead = nullptr;

	UPROPERTY(EditAnywhere, Category = "Tank/Component")
	TSubclassOf<ATankCanonComponent> m_tankCanonComponentClass;
	UPROPERTY(BlueprintReadWrite, Category = "Tank/Component")
	ATankCanonComponent* m_tankCanon = nullptr;

	///////////////////////////// Movement //////////////////////////////

	UPROPERTY()
	UTankCharacterMovementComponent* m_tankMovementComponent = nullptr;

	//////////////////// Settings //////////////////////
	UPROPERTY(EditAnywhere, Category = "Tank/Settings/Canon")
	float m_minPitchCanonRotation = 0;
	float m_maxPitchCanonRotation = 10;

	UPROPERTY(BlueprintReadWrite)
	bool bIsTankInit;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


/////////////// Construction Preview ////////////////

	void ConstructTankBodyPivot();
	void ConstructTankHeadPivot();
	void ConstructTankCanonPivot();

	void HideSkPreview() const;

//////////////// Tank Component ////////////////

	//Template Function for creating TankComponent
	template<class T>
	typename TEnableIf<TIsDerivedFrom<T, ATankComponent>::IsDerived, T*>::Type
		SpawnTankComponent(TSubclassOf<T> TankComponentClass, const FTransform& Transform, const FActorSpawnParameters& SpawnParams);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(const float inputVal);
	void MoveRight(const float inputVal);
	void RotateTopPivotYaw(const float inputVal);
	void RotateTopPivotPitch(const float inputVal);

	void ApplyNewMovementDirection(const FVector direction, const float scale);
	void ApplyNewRotation(const float scale);
	void ApplyNewTopPivotRotationYaw(const float scale);
	void ApplyNewTopPivotRotationPitch(const float scale);

	bool CheckPitchCanonRotation(float NextAddValue) const;

	void PrimaryShoot();

	virtual void InitTank();

	virtual ATankBodyComponent* SpawnBodyComponent(TSubclassOf<ATankBodyComponent> BodyClass);
	virtual ATankHeadComponent* SpawnHeadComponent(TSubclassOf<ATankHeadComponent> HeadClass);
	virtual ATankCanonComponent* SpawnCanonComponent(TSubclassOf<ATankCanonComponent> CanonClass);

	virtual bool CheckTankHeadComponent() const;

	virtual FActorSpawnParameters GetDefaultSpawnParams();
	//////////////////////// Getters /////////////////////////
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	USceneComponent* GetBodyPivot() const;
	UFUNCTION(BlueprintPure, BlueprintCallable)
	USceneComponent* GetHeadPivot() const;
	UFUNCTION(BlueprintPure, BlueprintCallable)
	USceneComponent* GetCanonPivot() const;
};
