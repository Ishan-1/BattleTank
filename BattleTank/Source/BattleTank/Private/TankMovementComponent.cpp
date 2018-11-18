// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet) || !ensure(RightTrackToSet))
	{
		
			return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}
void UTankMovementComponent::IntendMoveForward(float Throw)
{

	if (!ensure(LeftTrack) || !ensure(RightTrack))
	{
			return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack))
	{
		
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
	
}
