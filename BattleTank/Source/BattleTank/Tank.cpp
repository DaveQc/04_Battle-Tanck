// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
//#include "TankMovementComponent.h"
//#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	/*TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));*/
//	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

// Called every frame
/*void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

// Called to bind functionality to input
/*void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

/*void ATank::AimAt(FVector OUTHitLocation) {

	if (!TankAimingComponent)
	{
		return;
	}
	
	
	TankAimingComponent->AimAt(OUTHitLocation, LaunchSpeed);
	


}*/

/*void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
	
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;

}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {

	TankAimingComponent->SetTurretReference(TurretToSet);

}*/



