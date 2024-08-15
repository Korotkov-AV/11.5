// Fill out your copyright notice in the Description page of Project Settings.


#include "pro3ReloadFinishedAnimNotify.h"

void Upro3ReloadFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifyReloadFinished.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}