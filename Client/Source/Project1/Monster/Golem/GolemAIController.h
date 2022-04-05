// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MonsterAIController.h"
#include "GolemAIController.generated.h"

UCLASS()
class PROJECT1_API AGolemAIController : public AMonsterAIController
{
	GENERATED_BODY()
	
	public:
	AGolemAIController();

	protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
