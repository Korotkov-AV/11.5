// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "pro3BaseWeapon.generated.h"

class USkeletalMeshComponent;

DECLARE_DELEGATE(FOnNotifyEmptyClip);

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};

UCLASS()
class PRO3_API Apro3BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Apro3BaseWeapon();
	void Fire();
	void ChangeClip();

	bool IsCurrentClipFull() const;

	FOnNotifyEmptyClip NotifyEmptyClip;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{ 30, 0, true };

	virtual void BeginPlay() override;

	void Shoot();

	void DecrementBullets();
	bool IsCurrentClipEmpty() const;


private:
	FAmmoWeapon CurrentAmmoWeapon;

public:	

	virtual void Tick(float DeltaTime) override;


};
