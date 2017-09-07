// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIControler.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
//#include "Tank.h"





void ATankAIControler::BeginPlay()
{
	Super::BeginPlay();
	//...
}


void ATankAIControler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (PlayerTank)
	{
		//todo move towards the player

		MoveToActor(PlayerTank, AcceptanceRadius);
		//aim at the player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}

		
	}

}






