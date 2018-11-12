// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTankPlayerController.h"
#include "TankAimingComponent.h"


void AMyTankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AutoComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
    if(AutoComponent)
	FoundAimingComponent(AutoComponent);
	else
		UE_LOG(LogTemp,Warning,TEXT("Attach a aiming component"))
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
	FVector HitLocation; // Out parameter
	bool bGotHitLocation = GetHitSightRayLocation(HitLocation);
	if (bGotHitLocation) // Has "side-effect", is going to line trace
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}
bool AMyTankPlayerController::GetHitSightRayLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return false;
}
bool AMyTankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return  DeprojectScreenPositionToWorld(
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
		ECollisionChannel::ECC_Camera)
		)
	{
		HitLocation=HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}