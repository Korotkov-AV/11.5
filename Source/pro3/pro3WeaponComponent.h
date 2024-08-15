// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "pro3BaseWeapon.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "pro3WeaponComponent.generated.h"

class Apro3BaseWeapon;
class UAnimMontage; 


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRO3_API Upro3WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Upro3WeaponComponent();
	void Fire();
	void StopFire();
	void StartFire();

	void Reload();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<Apro3BaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* ReloadMontage;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	Apro3BaseWeapon* Weapon = nullptr;

	bool AnimReloading = false;

	void SpawnWeapon();
	void InitAnimNotify();

	void OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh);
	bool CanReload() const;

	FTimerHandle TimerHandle;
};
