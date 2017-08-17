// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIControler.h"


void ATankAIControler::BeginPlay()
{
	Super::BeginPlay();

	//...

	UE_LOG(LogTemp, Warning, TEXT("AI Controler begin play"));
	auto ControledTank = GetControledTank();


	if (!ControledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIControler Not Posseing Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIcontroler possesing %s"), *ControledTank->GetName());
	}

}


ATank* ATankAIControler::GetControledTank() const {

	return Cast<ATank>(GetPawn());


}

