// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
	//ctrl + f11 + alt
	//Using Ctrl + Shift + B (vs code)

	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->TargetArmLength = 1400;
	//SpringArm->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->SetFieldOfView(FOV);
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld()) {
		if (IsValid(CursorMaterial)) {
			Cursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
		}
	}
}

void ADefaultCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ADefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ADefaultCharacter::Sprint()
{
	dIsSprint = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ADefaultCharacter::StopSprint()
{
	dIsSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ADefaultCharacter::decreaseStamina()
{
	stamina -= minusStamina;
}

void ADefaultCharacter::increaseStamina()
{
	stamina += plusStamina;

}

// Called every frame
void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotationPlayerOnCursor();

	if (dIsSprint && stamina > 0.0f) {
		decreaseStamina();
	}
	if (!dIsSprint && stamina < 1000.0f) {
		increaseStamina();
	}
	if (FMath::IsNearlyZero(stamina)) {
		StopSprint();
	}
}	

// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADefaultCharacter::MoveRight);


	PlayerInputComponent->BindAction("sprint",IE_Pressed, this, &ADefaultCharacter::Sprint);
	PlayerInputComponent->BindAction("sprint",IE_Released, this, &ADefaultCharacter::StopSprint);


}

void ADefaultCharacter::RotationPlayerOnCursor()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (Cursor)
		{
			Cursor->SetWorldLocation(ResultHit.Location);
		}
	}
}