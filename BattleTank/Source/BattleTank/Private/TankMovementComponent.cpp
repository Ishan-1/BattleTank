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
void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{ 
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ResultForward = FVector::DotProduct(TankForward, AIForwardIntention);
	auto ResultRight = FVector::CrossProduct(TankForward,AIForwardIntention).Z;
	IntendMoveForward(ResultForward);
	IntendMoveRight(ResultRight);
	//UE_LOG(LogTemp,Warning,TEXT("%s trying to move towards: %s"),*HName,*MoveVelocityString)
}
