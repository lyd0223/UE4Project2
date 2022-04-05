// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"

#include "InventoryManager.generated.h"

UCLASS()
class PROJECT1_API UInventoryManager : public UObject
{
	GENERATED_BODY()

	friend class UProject1GameInstance;

private:
	UInventoryManager();

private:
	TArray<FItem*> m_ItemArray;
	uint8 m_MaxWeight;
	
	ACharacter* m_OwnerCharacter;
	
public:
	TArray<FItem*>& GetItemArray()
	{
		return m_ItemArray;
	}
	void SetOwnerCharacter(ACharacter* Character)
	{
		m_OwnerCharacter = Character;
	}
private:
	void Init();

public:
	void AddItem(FItem* Item);
	void DeductItem(FItem* Item);

};
