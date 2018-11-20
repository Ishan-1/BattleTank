// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}
int32 UTankAimingComponent::GetRoundsLeft() const
{
	return AmmoCount;
}
// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetWorld()->GetTimeSeconds() - LastFireTime < ReloadTimeinSeconds)
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else if (AmmoCount == 0)
	{
		FiringState = EFiringStatus::OutOfAmmo;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) return;
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace // Paramater must be present to prevent bug
	);
	if(bHaveAimSolution)
	{
		auto Desired = OutLaunchVelocity.GetSafeNormal();
		AimDirection = Desired;
		MoveBarrelTowards(Desired);
	}
}
void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}
void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringStatus::Locked && FiringState == EFiringStatus::Aiming &&AmmoCount>0)
	{
		if (!ensure(Barrel)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);
		AmmoCount--;
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}
void UTankAimingComponent::MoveBarrelTowards(FVector TargetAimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
			return;
	}
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = TargetAimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;
	if (FMath::Abs(DeltaRotator.Yaw) < 180.f)
		Turret->Rotate(DeltaRotator.Yaw);
	else
		Turret->Rotate(-DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; }
	if (AimDirection.Equals(Turret->GetForwardVector(),0.1f))
	{
		return false;
	}
	return true;
}
