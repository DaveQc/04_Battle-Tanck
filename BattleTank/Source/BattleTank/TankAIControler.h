// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIControler.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIControler : public AAIController
{
	GENERATED_BODY()

private:
	

	//how close the ai tank get
	float AcceptanceRadius = 3000;


public:


	virtual void BeginPlay() override;

	virtual void Tick(float) override;
	
};
