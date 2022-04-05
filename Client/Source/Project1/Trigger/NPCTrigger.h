// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SphereTrigger.h"
#include "NPCTrigger.generated.h"

UCLASS()
class PROJECT1_API ANPCTrigger : public ASphereTrigger
{
	GENERATED_BODY()

public:
	ANPCTrigger();

protected:
	class ANPC* m_OwnerNPC;

public:
	void SetOwnerNPC(class ANPC* NPC)
	{
		m_OwnerNPC = NPC;
	}
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void TriggerBegin();

	UFUNCTION()
	void TriggerEnd();

	void SetTriggerSize(float Radious);
};
