// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerControler.h"


void ATankPlayerControler::BeginPlay()
{
	Super::BeginPlay();

	//...

	UE_LOG(LogTemp, Warning, TEXT("Player Controler begin play"));
	auto ControledTank = GetControledTank();


	if (!ControledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerControler Not Posseing Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controler possesing %s"), *ControledTank->GetName());
	}

}



void ATankPlayerControler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTownardsCrosshair();

	//UE_LOG(LogTemp, Warning, TEXT("Player Controler Ticking"));
}





ATank* ATankPlayerControler::GetControledTank() const {

	return Cast<ATank>(GetPawn());


}

void ATankPlayerControler::AimTownardsCrosshair() {

	if (!GetControledTank()){return;}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) // has side effect , is going to line trace
	{
		GetControledTank()->AimAt(HitLocation);

	}


}


///get world location of linetrace trough crosshair, true if hits landscape
bool ATankPlayerControler::GetSightRayHitLocation(FVector& OUTHitLocation) const {


	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("screen location: %s"), *ScreenLocation.ToString());
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("look direction: %s"), *LookDirection.ToString());
		GetLookVectorHitLocation(LookDirection, OUTHitLocation);
	}

	return true;


}

bool ATankPlayerControler::GetLookVectorHitLocation(FVector LookDirection, FVector& OUTHitLocation) const {

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		OUTHitLocation = HitResult.Location;
		return true;
	}
	return false;
}

bool ATankPlayerControler::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {

	FVector CameraWorldLocation; //to be discarded
	
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
		
	

}


