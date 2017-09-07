// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"



UTankTrack::UTankTrack() {

	PrimaryComponentTick.bCanEverTick = false;
	
}

void UTankTrack::BeginPlay() {

	Super::BeginPlay();

	//...
	
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);



}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {

	/*UE_LOG(LogTemp, Warning, TEXT("i'm hit i'm hit!"));*/

	DriveTrack();
	
	ApplySidewaysForce();
	
	CurrentThrottle = 0;

}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	
	ReceiveTick(DeltaTime);
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//...
	
	

	//UE_LOG(LogTemp, Warning, TEXT("tank track tick"));

}

void UTankTrack::ApplySidewaysForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	auto tankroot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto CorrectionForce = (tankroot->GetMass() * CorrectionAcceleration) / 2; /*because there is 2 tracks*/

	tankroot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack() {




	//clamp actual throttle value so player cant over drive
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}





