// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"


<<<<<<< HEAD

UTankTrack::UTankTrack() {

	PrimaryComponentTick.bCanEverTick = true;
	
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	
	//ReceiveTick(DeltaTime);
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//...
	
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	auto tankroot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto CorrectionForce = (tankroot->GetMass() * CorrectionAcceleration) / 2; //because there is 2 tracks

	tankroot->AddForce(CorrectionForce);
	
	UE_LOG(LogTemp, Warning, TEXT("tank track tick"));

}


=======
>>>>>>> parent of 0791044... 0.0.42 [tick track not working]
void UTankTrack::SetThrottle(float Throttle) {




	//clamp actual throttle value so player cant over drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}



