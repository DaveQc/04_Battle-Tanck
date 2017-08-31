// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


//#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerControler.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerControler : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControledTank() const;

public:

	
 	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	void AimTownardsCrosshair();

	//return en OUT peremeter
	bool GetSightRayHitLocation(FVector& OUTHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

private:

	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.3333;
	
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0;
};
