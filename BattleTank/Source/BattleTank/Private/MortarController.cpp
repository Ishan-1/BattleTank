// Copyright Idiocy

#include "MortarController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void AMortarController::BeginPlay()
{
	Super::BeginPlay();
}
void AMortarController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ensure(PlayerTank))
	{
		if (!PlayerTank)
			return;
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
		{
			AimingComponent->FireMultiple(3);
		}
	}
}

void AMortarController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &AMortarController::OnPossessedMortarDeath);
	}
}

void AMortarController::OnPossessedMortarDeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

