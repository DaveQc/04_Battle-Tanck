// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIControler.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIControler : public AAIController
{
	GENERATED_BODY()

public:
	
		ATank* GetControledTank() const;

	virtual void BeginPlay() override;
	
};
