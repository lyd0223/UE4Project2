// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../MonsterAIController.h"
#include "RampageAIController.generated.h"

UCLASS()
class PROJECT1_API ARampageAIController : public AMonsterAIController
{
	GENERATED_BODY()
	
	public:
	ARampageAIController();

	protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
