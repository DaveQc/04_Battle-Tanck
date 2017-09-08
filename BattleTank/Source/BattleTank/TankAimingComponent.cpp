// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankBarrel.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

/*void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	
	if (!BarrelToSet)
	{
		return;
	}
	Barrel = BarrelToSet;


}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	
	if (!TurretToSet)
	{
		return;
	}
	
	Turret = TurretToSet;


}*/


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	
	LastFireTime = FPlatformTime::Seconds();

	
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}



bool UTankAimingComponent::IsBarrelMoving() {
	
	if (!Barrel)
	{
		return false;
	}

	auto BarrelFoward = Barrel->GetForwardVector();
	return !BarrelFoward.Equals(AimDirection, 0.01);

}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < RealoadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	

	//UE_LOG(LogTemp, Warning, TEXT("tank aiming component tick"));
}


int UTankAimingComponent::GetRoundsLeft() const {

	return RoundsLeft;

}

void UTankAimingComponent::AimAt(FVector OUTHitLocation) {

	if (!Barrel)
	{
		return;
	}

	FVector OUTLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this, 
		OUTLaunchVelocity, 
		StartLocation, 
		OUTHitLocation, 
		LaunchSpeed, 
		false, 
		0, 
		0, 
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)
	{
		AimDirection = OUTLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);


	}

}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	
	if (!Barrel || !Turret)
	{
		return;
	}
	
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotation = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotation - BarrelRotation;

	

	Barrel->Elevate(DeltaRotation.Pitch);

	if (FMath::Abs(DeltaRotation.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotation.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotation.Yaw);
	}

	
}



void UTankAimingComponent::Fire() {

	

	if (!Barrel && !ProjectileBluePrint)
	{
		return;
	}
	
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{// spawn a projectil at the socket location

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

