// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "BoxTrigger.h"
#include "LootBoxTrigger.generated.h"

UCLASS()
class PROJECT1_API ALootBoxTrigger : public ABoxTrigger
{
	GENERATED_BODY()
	
	public:
	ALootBoxTrigger();

	protected:
	class ALootBox* m_OwnerLootBox;

	bool m_IsTriggerOn;
	
	public:
	void SetOwnerLootBox(class ALootBox* LootBox)
	{
		m_OwnerLootBox = LootBox;
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

	void SetTriggerSize(FVector SizeVector);
};
