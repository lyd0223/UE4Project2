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
	UPROPERTY()
	class UStoreListItemWidget* m_OwnerWidget;

	FItem* m_Item;
	class UStoreWidget* m_StoreWidget;

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

	class UStoreWidget* GetStoreWidget() const
	{
		return m_StoreWidget;
	}
	void SetStoreWidget(UStoreWidget* _StoreWidget) 
	{
		m_StoreWidget = _StoreWidget;
	}
};
