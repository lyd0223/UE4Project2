// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "LootListItemData.generated.h"

UCLASS()
class PROJECT1_API ULootListItemData : public UObject
{
	GENERATED_BODY()

public:
	ULootListItemData();

protected:
	FItem* m_Item;

	class ULootListItemWidget* m_OwnerItemWidget;
	
public:
	void SetItem(FItem* Item)
	{
		m_Item = Item;
	}

	FItem* GetItem() const
	{
		return m_Item;
	}

	void SetOwnerItemWidget(class ULootListItemWidget* ItemWidget)
	{
		m_OwnerItemWidget = ItemWidget;
	}
	ULootListItemWidget* GetOwnerItemWidget() const
	{
		return m_OwnerItemWidget;
	}
};
