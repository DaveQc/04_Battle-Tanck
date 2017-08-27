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
	UE_LOG(LogTemp, Warning, TEXT("hit location %s"), *HitLocation.ToString());

	}


}


///get world location of linetrace trough crosshair, true if hits landscape
bool ATankPlayerControler::GetSightRayHitLocation(FVector& OUTHitLocation) const {

	OUTHitLocation = FVector(1.0);
	return true;


}


