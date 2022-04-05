// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Monster.h"
#include "MinionGunner.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API AMinionGunner : public AMonster
{
	GENERATED_BODY()
	
	public:
	AMinionGunner();

	protected:

	protected:
	virtual void BeginPlay() override;

	public:
	virtual void Tick(float DeltaTime) override;

	public:
	virtual void NormalAttack();
};
