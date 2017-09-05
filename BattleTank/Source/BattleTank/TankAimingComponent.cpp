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
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	UE_LOG(LogTemp, Warning, TEXT("tank aiming component tick"));
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
		auto AimDirection = OUTLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);


	}

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
	Turret->Rotate(DeltaRotation.Yaw);
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {

	Barrel = BarrelToSet;
	Turret = TurretToSet;


}

void UTankAimingComponent::Fire() {

	bool isReloeded = (FPlatformTime::Seconds() - LastFireTime) > RealoadTimeInSeconds;

	if (!Barrel && !ProjectileBluePrint)
	{
		return;
	}
	
	if (Barrel && isReloeded)
	{// spawn a projectil at the socket location

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

