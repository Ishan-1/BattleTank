// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};
class UTankBarrel;
class UTankTurret;
class AProjectile;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Reloading;
	UPROPERTY(EditDefaultsOnly, Category = "State")
		int32 AmmoCount = 4;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector WorldSpaceAim);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Fire();
		void FireMultiple(int times);
	EFiringStatus GetFiringState() const;
	UFUNCTION(BlueprintCallable, Category = "Firing")
		int32 GetRoundsLeft() const;
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	bool IsBarrelMoving() const;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 10000;//TODO find sensible default
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeinSeconds = 3;
	double LastFireTime = 0.0;
	double LastFireTime_M = 0.0;
	FVector AimDirection=FVector(0);
};
