// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "pro3WeaponComponent.h"
#include "DefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UDecalComponent;
class Upro3WeaponComponent;

UCLASS()
class PRO3_API ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	Upro3WeaponComponent* WeaponComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="Component")
	UCameraComponent *Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial;
	UPROPERTY()
	UDecalComponent *Cursor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.f, 40.f, 40.f);
	float YRotation = -75.0f;
	float FOV = 55.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void MouseWheel(float Value);

	void Sprint();
	void StopSprint();

	bool dIsSprint = false;
	//UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float minusStamina = -10.0f;
	//UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float plusStamina = 10.0f;
	//UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float stamina = 500.0f;

	void decreaseStamina();
	void increaseStamina();

	void RotationPlayerOnCursor();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	bool GetIsSprint() const { return dIsSprint; }
};
