// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "StoreListItemData.generated.h"

UCLASS()
class PROJECT1_API UStoreListItemData : public UObject
{
	GENERATED_BODY()

	
	public:
	UStoreListItemData();

	protected:
	FItem* m_Item;

	UPROPERTY()
	class UStoreListItemWidget* m_OwnerWidget;
	
	public:
	void SetItem(FItem* Item)
	{
		m_Item = Item;
	}

	FItem* GetItem() const
	{
		return m_Item;
	}

	void SetOwnerWidget(class UStoreListItemWidget* OwnerWidget)
	{
		m_OwnerWidget = OwnerWidget;
	}
	class UStoreListItemWidget* GetOwnerWidget() const
	{
		return m_OwnerWidget;
	}
};
