// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond*GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation=FMath::Clamp<float>(RawNewElevation, MinElevationDegrees,MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation,0.0f, 0.f));
}


