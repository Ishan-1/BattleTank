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
void AMyTankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}
void AMyTankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;///OUT parameter
	if(GetHitSightRayLocation(HitLocation))
	UE_LOG(LogTemp,Warning,TEXT("%s"),*(HitLocation.ToString()))
}
bool AMyTankPlayerController::GetHitSightRayLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX*CrossHairXLocation, ViewPortSizeY*CrossHairYLocation);
	FVector CameraWorldPosition,WorldPosition;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldPosition, WorldPosition))
	{
		UE_LOG(LogTemp,Warning,TEXT("Look direction: %s"),*(WorldPosition.ToString()))
	}
	return true;
}