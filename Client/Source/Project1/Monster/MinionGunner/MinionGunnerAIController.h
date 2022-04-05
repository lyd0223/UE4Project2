// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MonsterAIController.h"
#include "MinionGunnerAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API AMinionGunnerAIController : public AMonsterAIController
{
	GENERATED_BODY()
	
	public:
	AMinionGunnerAIController();

	protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
