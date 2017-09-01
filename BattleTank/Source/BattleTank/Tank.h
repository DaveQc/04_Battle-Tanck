// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
//class UTankMovementComponent;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	/*UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;*/

public:	
	// Called every frame
/*	virtual void Tick(float DeltaTime) override;*/

	// Called to bind functionality to input
	/*virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;*/

	void AimAt(FVector OUTHitLocation);

	/*UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);*/

	UFUNCTION(BlueprintCallable)
		void Fire();


private:
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 8000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float RealoadTimeInSeconds = 0.3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBluePrint; 

	UTankBarrel* Barrel = nullptr; //TODO Revome 

	
	
	

	double LastFireTime = 0;
	
};
