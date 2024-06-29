// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UDecalComponent;

UCLASS()
class PRO3_API ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultCharacter();

protected:
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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
