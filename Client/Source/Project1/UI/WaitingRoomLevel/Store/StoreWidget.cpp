// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreWidget.h"


void UStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_SaleItemListView = Cast<UListView>(GetWidgetFromName(TEXT("SaleItemListView")));
}

void UStoreWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}
