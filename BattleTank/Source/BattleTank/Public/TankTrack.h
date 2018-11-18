// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to move the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();
	void ApplySidewaysForce();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable,Category=Input)
	void SetThrottle(float Throttle);
	//Max force per track
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce=400000.f;
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComponent,FVector NormalImpulse,const FHitResult& Hit);
};
