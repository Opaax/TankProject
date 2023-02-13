// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/TankComponent/TankComponent.h"

//Tank
#include "TankGame/Public/TankBaseCharacter.h"
#include "TankGame/Public/Character/TankCharacter.h"

// UE
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ATankComponent::ATankComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root_COMP"));
	SetRootComponent(m_rootComponent);

	m_skMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SK_Mesh"));
	m_skMesh->SetupAttachment(m_rootComponent);
}

// Called when the game starts or when spawned
void ATankComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATankComponent::InitComponent(ATankBaseCharacter* NewOwner)
{
	m_ownerCharacter = NewOwner;

	AttachToTank();
}

void ATankComponent::AttachToTank() 
{
	if (!IsValid(m_ownerCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("Tank Upgrade, Look to attach on character but the character is not valid"))
		return;
	}

	FAttachmentTransformRules lTransRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, false);

	AttachToComponent(m_ownerCharacter->GetHeadPivot(), lTransRules, m_NameSocket);
}

bool ATankComponent::AddChild(ATankComponent* NewChild)
{
	bool* lBool = nullptr;

	m_children.Add(NewChild, lBool);

	if (lBool != nullptr && !lBool)
	{
		UE_LOG(LogTemp, Error, TEXT("TankComponent %s, had already this child %s"), *GetName(), *NewChild->GetName());

		return false;
	}

	return true;
}

bool ATankComponent::RemoveChild(ATankComponent* ChildToRemove)
{
	m_children.Remove(ChildToRemove);

	if (m_children.Contains(ChildToRemove))
		return false;
	else
		return true;
}

TArray<ATankComponent*> ATankComponent::GetChildren() const
{
	return m_children.Array();
}
