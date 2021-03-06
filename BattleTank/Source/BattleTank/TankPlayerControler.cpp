// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerControler.h"
#include "TankAimingComponent.h"
//#include "Tank.h"



void ATankPlayerControler::BeginPlay()
{
	Super::BeginPlay();

	//...

	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controler cant find aiming component at begin play"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Player Controler begin play"));
	auto ControledTank = GetPawn();


	if (!ControledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerControler Not Posseing Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controler possesing %s"),  GetPawn());
	}

}



void ATankPlayerControler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTownardsCrosshair();

	//UE_LOG(LogTemp, Warning, TEXT("Player Controler Ticking"));
}





/*ATank* ATankPlayerControler::GetPawn() const {

	return GetPawn();


}*/

void ATankPlayerControler::AimTownardsCrosshair() {

	if (!GetPawn())
	{
		return;
	}
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}



	FVector HitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);

	UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation %i"), bGotHitLocation);


	if (bGotHitLocation) // has side effect , is going to line trace
	{
		AimingComponent->AimAt(HitLocation);

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
		return GetLookVectorHitLocation(LookDirection, OUTHitLocation);
	}

	return false;


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


