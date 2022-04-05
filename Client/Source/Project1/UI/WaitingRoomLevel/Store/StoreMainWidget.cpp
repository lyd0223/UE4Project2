// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreMainWidget.h"
#include "StoreWidget.h"
#include "../../Inventory/InventoryWidget.h"

void UStoreMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_StoreWidget = Cast<UStoreWidget>(GetWidgetFromName(TEXT("UI_Store")));
	m_InventoryWidget = Cast<UInventoryWidget>(GetWidgetFromName(TEXT("UI_Inventory")));
	
}

void UStoreMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}
