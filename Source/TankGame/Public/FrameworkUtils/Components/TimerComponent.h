// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TimerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimerCallBack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimerCallBackOneParam, float, timerParam);

UENUM()
enum class ETimerType :uint8
{
	Inc,
	Dec
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTimerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	float m_time = 0;
	float m_currentTime = 0;
	float m_timeRatio = 0;
	float m_prevSec = 0;
	float m_prevMinute = 0;

	ETimerType m_timerType = ETimerType::Dec;

public:

	UPROPERTY(Replicated, BlueprintReadWrite)
	bool bIsPause = false;
	UPROPERTY(Replicated, BlueprintReadWrite)
	bool bIsLaunched = false;
	UPROPERTY(Replicated, BlueprintReadWrite)
	bool bIsDebug = false;

	UPROPERTY(BlueprintReadWrite)
	float currentSec = 0;
	UPROPERTY(BlueprintReadWrite)
	float currentMinute = 0;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FTimerCallBack OnTimerOver;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FTimerCallBack OnTimerLaunched;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FTimerCallBackOneParam OnSecondeChange;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FTimerCallBackOneParam OnMinuteChange;

protected:

	void CheckEndTimer();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps
	(
		TArray< FLifetimeProperty >& OutLifetimeProps
	) const override;

	UFUNCTION(BlueprintCallable)
	void Launch(float NewTime, ETimerType WantedType, bool Debug = false);
	UFUNCTION(BlueprintCallable)
	void Stop();
	UFUNCTION(BlueprintCallable)
	void Pause();
	UFUNCTION(BlueprintCallable)
	void Resume();
	UFUNCTION(BlueprintCallable)
	void Reset();
	UFUNCTION(BlueprintCallable)
	float GetTimerRatio();		
};
