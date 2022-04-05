// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoxTrigger.h"
#include "PortalTrigger.generated.h"

UCLASS()
class PROJECT1_API APortalTrigger : public ABoxTrigger
{
	GENERATED_BODY()
	
	public:
	APortalTrigger();
	
	protected:
	virtual void BeginPlay() override;

	public:
	virtual void Tick(float DeltaTime) override;

	public:
	UFUNCTION()
	void TriggerBegin();

	UFUNCTION()
	void TriggerEnd();

	void SetTriggerSize(FVector SizeVector);
};
