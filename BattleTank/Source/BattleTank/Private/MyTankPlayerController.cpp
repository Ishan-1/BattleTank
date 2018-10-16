// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/MyTankPlayerController.h"

void AMyTankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank())
	{
		UE_LOG(LogTemp,Warning,TEXT("%s possessed"),*(GetControlledTank()->GetName()))
	}
	else
		UE_LOG(LogTemp,Warning,TEXT("No tank found"))
}
ATank* AMyTankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

