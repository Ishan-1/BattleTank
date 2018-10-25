// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if(GetPlayerTank())
		UE_LOG(LogTemp,Warning,TEXT("The player tank is %s"),*(GetPlayerTank()->GetName()))
	else
		UE_LOG(LogTemp,Error,TEXT("No player tank found"))
}
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) { return nullptr; }
	return Cast<ATank>(PlayerTank);
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

