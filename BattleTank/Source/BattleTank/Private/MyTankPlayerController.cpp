// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTankPlayerController.h"
#include "TankAimingComponent.h"


void AMyTankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AutoComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(ensure(AutoComponent))
	FoundAimingComponent(AutoComponent);
}
void AMyTankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}
void AMyTankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this,&AMyTankPlayerController::OnPlayerTankDeath);
	}
}
void AMyTankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	FVector HitLocation; // Out parameter
	bool bGotHitLocation = GetHitSightRayLocation(HitLocation);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	if (bGotHitLocation) // Has "side-effect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
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
	if (!GetPawn()) { return false; }
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
	if (!GetPawn()) { return false; }
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation=HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}

void AMyTankPlayerController::OnPlayerTankDeath()
{
	if (!GetPawn()) { return; }
	StartSpectatingOnly();
}
