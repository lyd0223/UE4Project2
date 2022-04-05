// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../NPC.h"
#include "Gremlin.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API AGremlin : public ANPC
{
	GENERATED_BODY()
	
	public:
	AGremlin();
	
	protected:
	virtual void BeginPlay() override;

	public:
	virtual void Tick(float DeltaTime) override;
};
