// Fill out your copyright notice in the Description page of Project Settings.


#include "pro3ReloadFinishedAnimNotify.h"
#include "pro3WeaponComponent.h"
#include "pro3BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Components/ActorComponent.h"

// Sets default values for this component's properties
Upro3WeaponComponent::Upro3WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void Upro3WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
	InitAnimNotify();
	
}

void Upro3WeaponComponent::Fire()
{
	if (Weapon && !AnimReloading)
	{
		Weapon->Fire();
	}
}

void Upro3WeaponComponent::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void Upro3WeaponComponent::StartFire()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &Upro3WeaponComponent::Fire, 0.6f, true, 0.0f);
}

void Upro3WeaponComponent::Reload()
{
	if (!CanReload()) return;
	AnimReloading = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);
	Weapon->ChangeClip();
}

// Called every frame
void Upro3WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void Upro3WeaponComponent::SpawnWeapon()
{
	Weapon = GetWorld()->SpawnActor<Apro3BaseWeapon>(WeaponClass);
	if (Weapon)
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "r_Weapon_Socket");
			Weapon->NotifyEmptyClip.BindUObject(this, &Upro3WeaponComponent::Reload);
		}
	}
}

void Upro3WeaponComponent::InitAnimNotify()
{
	if (!ReloadMontage)return;

	const auto NotifiesEvents = ReloadMontage->Notifies;
	for (auto NotifyEvent : NotifiesEvents)
	{
		auto ReloadFinish = Cast<Upro3ReloadFinishedAnimNotify>(NotifyEvent.Notify);
		if (ReloadFinish)
		{
			ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &Upro3WeaponComponent::OnNotifyReloadFinished);
			break;
		}
	}
}

void Upro3WeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetMesh() == SkeletalMesh)
	{
		AnimReloading = false;
	}
}

bool Upro3WeaponComponent::CanReload() const
{
	return (!AnimReloading && !Weapon->IsCurrentClipFull());
}
