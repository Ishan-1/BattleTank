// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("Track reference missing"))
			return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}
void UTankMovementComponent::IntendMoveForward(float Throw)
{

	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("Track reference missing"))
			return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("Track reference missing"))
			return;
	}
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveLeft(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("Track reference missing"))
			return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::IntendMoveBackward(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("Track reference missing"))
			return;
	}
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(-Throw);
}