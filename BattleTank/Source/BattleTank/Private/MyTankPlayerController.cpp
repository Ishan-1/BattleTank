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
	if (GetHitSightRayLocation(HitLocation))
		GetControlledTank()->AimAt(HitLocation);
}
bool AMyTankPlayerController::GetHitSightRayLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX*CrossHairXLocation, ViewPortSizeY*CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return true;
}
bool AMyTankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}
bool AMyTankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility)
		)
	{
		HitLocation=HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}