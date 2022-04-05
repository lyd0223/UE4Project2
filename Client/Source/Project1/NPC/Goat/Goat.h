// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../NPC.h"
#include "Goat.generated.h"

UCLASS()
class PROJECT1_API AGoat : public ANPC
{
	GENERATED_BODY()

	public:
	AGoat();
	
	protected:
	virtual void BeginPlay() override;

	public:
	virtual void Tick(float DeltaTime) override;

};
