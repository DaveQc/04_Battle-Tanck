// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIControler.h"
#include "Engine/World.h"
#include "Tank.h"





void ATankAIControler::BeginPlay()
{
	Super::BeginPlay();
	//...
}


void ATankAIControler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		//todo move towards the player
		//aim at the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire(); //TODO dont fire every frame
	}

}






