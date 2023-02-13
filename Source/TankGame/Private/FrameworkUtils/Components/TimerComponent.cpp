// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameworkUtils/Components/TimerComponent.h"

void UTimerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

// Sets default values for this component's properties
UTimerComponent::UTimerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTimerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsLaunched && !bIsPause)
	{
		switch (m_timerType)
		{
		case ETimerType::Dec:
			m_currentTime -= DeltaTime;
			break;
		case ETimerType::Inc:
			m_currentTime += DeltaTime;
		default:
			break;
		}

		currentSec = FMath::CeilToInt(m_currentTime) % 60;
		currentMinute = FMath::CeilToInt(m_currentTime) / 60;

		if (bIsDebug)
			GEngine->AddOnScreenDebugMessage(6, 5, FColor::Cyan, "current time:" + FString::SanitizeFloat(m_currentTime));

		if (currentSec != m_prevSec)
		{
			m_prevSec = currentSec;

			OnSecondeChange.Broadcast(currentSec);
		}

		if (currentMinute != m_prevMinute)
		{
			m_prevMinute = currentMinute;

			OnMinuteChange.Broadcast(currentMinute);
		}

		CheckEndTimer();
	}
}

/// <summary>
/// Launch the timer
/// </summary>
/// <param name="newTime">time in sec</param>
/// <param name="wantedType">type of timer. Incremented, Decremented</param>
/// <param name="debug">print message callback (OnLaunch,OnPause,OnResume,OnStop,OnReset,OnStop)</param>
void UTimerComponent::Launch(float NewTime, ETimerType WantedType, bool Debug)
{
	m_time = NewTime;

	m_timerType = WantedType;

	switch (m_timerType)
	{
	case ETimerType::Inc:
		m_currentTime = m_prevSec = currentSec = currentMinute = m_prevMinute = 0;
		break;
	case ETimerType::Dec:
		m_currentTime = m_time;
		currentSec = FMath::CeilToInt(m_currentTime) % 60;
		currentMinute = FMath::CeilToInt(m_currentTime) / 60;
		break;
	default:
		break;
	}

	bIsLaunched = true;
	bIsPause = false;
	bIsDebug = Debug;

	if (bIsDebug)
		GEngine->AddOnScreenDebugMessage(6, 5, FColor::Cyan, "current time :" + FString::SanitizeFloat(m_currentTime) + ", time: " + FString::SanitizeFloat(m_time));
}

void UTimerComponent::CheckEndTimer()
{
	if (m_currentTime >= m_time || m_currentTime <= 0)
	{
		bIsLaunched = false;
		bIsPause = false;

		OnTimerOver.Broadcast();

		if (bIsDebug)
			GEngine->AddOnScreenDebugMessage(6, 5, FColor::Cyan, "Timer done");
	}
}

/// <summary>
/// will reset the current in function of timer type
/// </summary>
void UTimerComponent::Reset()
{
	switch (m_timerType)
	{
	case ETimerType::Inc:
		m_currentTime = m_prevSec = currentSec = currentMinute = m_prevMinute = 0;
		break;
	case ETimerType::Dec:
		m_currentTime = m_time;
		currentSec = FMath::CeilToInt(m_currentTime) % 60;
		currentMinute = FMath::CeilToInt(m_currentTime) / 60;
		break;
	default:
		break;
	}

	if (bIsDebug)
		GEngine->AddOnScreenDebugMessage(6, 5, FColor::Cyan, "Timer Reset");
}

/// <summary>
/// Pause the timer
/// </summary>
void UTimerComponent::Pause()
{
	if (!bIsLaunched)
	{
		GEngine->AddOnScreenDebugMessage(6, 5, FColor::Red, "You are looking to Pause timer but the timer its stop or no lauched yet");
		return;
	}

	if (bIsDebug)
		GEngine->AddOnScreenDebugMessage(6, 5, FColor::Cyan, "Timer Pause");

	bIsPause = true;
}

/// <summary>
/// Will resume the timer
/// </summary>
void UTimerComponent::Resume()
{
	if (!bIsLaunched)
	{
		GEngine->AddOnScreenDebugMessage(6, 5, FColor::Red, "You are looking to Resume timer but the timer its stop or no lauched yet");
		return;
	}

	if (bIsDebug)
		GEngine->AddOnScreenDebugMessage(6, 5, FColor::Cyan, "Timer Resume");

	bIsPause = false;
}

/// <summary>
/// Stop the timer. After using you stop the timer can't be Reset, Pause or Resume. You have to relaunch the timer
/// </summary>
void UTimerComponent::Stop()
{
	if (bIsDebug)
		GEngine->AddOnScreenDebugMessage(6, 5, FColor::Cyan, "Timer Stop");

	bIsLaunched = false;
	bIsPause = false;
	bIsDebug = false;

	m_currentTime = m_prevSec = currentSec = currentMinute = m_prevMinute = 0;
}

/// <summary>
/// Get the ratio of current time
/// </summary>
/// <returns>0 to 1, if not launch return -1</returns>
float UTimerComponent::GetTimerRatio()
{
	if (!bIsLaunched) return -1;

	return m_currentTime / m_time;
}

