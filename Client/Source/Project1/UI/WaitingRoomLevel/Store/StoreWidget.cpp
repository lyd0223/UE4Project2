// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreWidget.h"

#include "BuyWidget.h"
#include "StoreListItemData.h"
#include "Project1/Project1GameInstance.h"


void UStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	m_StoreListView = Cast<UListView>(GetWidgetFromName(TEXT("SaleItemListView")));
	m_BuyWidget = Cast<UBuyWidget>(GetWidgetFromName(TEXT("UI_Buy")));
	
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetGameInstance());
	{
		FItem* Item = new FItem();
		Item->ItemTableInfo = GameInstance->FindItemTableInfo(TEXT("HP포션(소)"));
		Item->Count = 999;
		AddItemSaleItemListView(Item);
	}
	{
		FItem* Item = new FItem();
		Item->ItemTableInfo = GameInstance->FindItemTableInfo(TEXT("HP포션(중)"));
		Item->Count = 999;
		AddItemSaleItemListView(Item);
	}
	{
		FItem* Item = new FItem();
		Item->ItemTableInfo = GameInstance->FindItemTableInfo(TEXT("HP포션(대)"));
		Item->Count = 999;
		AddItemSaleItemListView(Item);
	}
	{
		FItem* Item = new FItem();
		Item->ItemTableInfo = GameInstance->FindItemTableInfo(TEXT("분노의영약"));
		Item->Count = 999;
		AddItemSaleItemListView(Item);
	}
	{
		FItem* Item = new FItem();
		Item->ItemTableInfo = GameInstance->FindItemTableInfo(TEXT("속도의영약"));
		Item->Count = 999;
		AddItemSaleItemListView(Item);
	}
}

void UStoreWidget::AddItemSaleItemListView(FItem* Item)
{
	//ItemData 설정.
	UStoreListItemData* ItemData = NewObject<UStoreListItemData>(this, UStoreListItemData::StaticClass());
	ItemData->SetItem(Item);
	ItemData->SetStoreWidget(this);
	m_StoreListView->AddItem(ItemData);
}