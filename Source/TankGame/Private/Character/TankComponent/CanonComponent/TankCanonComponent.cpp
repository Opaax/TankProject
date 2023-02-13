// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TankComponent/CanonComponent/TankCanonComponent.h"

//Tank
#include "TankGame/Public/TankBaseCharacter.h"
#include "TankGame/Public/Character/TankCharacter.h"

void ATankCanonComponent::AttachToTank()
{
	if (!IsValid(m_ownerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("Tank Upgrade, Look to attach on character but the character is not valid"))
			return;
	}

	FAttachmentTransformRules lTransRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, false);

	AttachToComponent(m_ownerCharacter->GetCanonPivot(), lTransRules, m_NameSocket);
}

