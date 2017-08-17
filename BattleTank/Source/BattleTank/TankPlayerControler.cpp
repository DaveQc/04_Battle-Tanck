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


ATank* ATankPlayerControler::GetControledTank() const {

	return Cast<ATank>(GetPawn());


}


