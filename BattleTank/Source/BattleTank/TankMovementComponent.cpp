// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include"Engine/World.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {

	if (!LeftTrackToSet || !RightTrackToSet)
	{
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;


}


void UTankMovementComponent::IntendMoveFoward(float Throw) {

	/*auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("time: %f :: intend move foward throw : %f"),Time, Throw);*/

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO prevent double speed

}


void UTankMovementComponent::IntendTurnRight(float Throw) {
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
	// TODO prevent double speed
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {

	//on need to call supper as we are replacing the functionality

	auto TankFoward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIFowardIntention = MoveVelocity.GetSafeNormal();
	auto FowardThrow = FVector::DotProduct(TankFoward, AIFowardIntention);

	IntendMoveFoward(FowardThrow);
	
	auto RightThrow = FVector::CrossProduct(TankFoward, AIFowardIntention).Z;
	IntendTurnRight(RightThrow);
	
	/*auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("time: %f :: %s vectoring"), Time, *TankName);*/

}



