// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIControler.h"




void ATankAIControler::BeginPlay()
{
	Super::BeginPlay();

	//...

	UE_LOG(LogTemp, Warning, TEXT("AI Controler begin play"));
	auto PlayerTank = GetPlayerTank();


	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controler can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIcontroler found player %s"), *(PlayerTank->GetName()));
	}

}


ATank* ATankAIControler::GetControledTank() const {

	return Cast<ATank>(GetPawn());


}

ATank * ATankAIControler::GetPlayerTank() const
{
	
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!PlayerPawn)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}

