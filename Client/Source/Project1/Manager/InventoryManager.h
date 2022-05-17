// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "Project1/Global/Message/ContentsStruct.h"

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
	uint8 m_NowWeight;

	uint64 m_Gold;
	
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
	uint64 GetGold() const
	{
		return m_Gold;
	}
	
private:
	void Init();

public:
	void AddGold(uint64 _Gold);
	void DeductGold(uint64 _Gold);
	void AddItem(FItem* Item);
	void DeductItem(FItem* Item);
	void SetUI(FItem* Item);
	void SetUI(uint64 _Gold);
	void SaveCharacterInfoInventoryData(FCharacterInfo& CharacterInfo);
	void LoadCharacterInfoInventoryData(const FCharacterInfo& CharacterInfo);

};
