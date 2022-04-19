// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreMainWidget.h"
#include "StoreWidget.h"
#include "Project1/UI/MenuWidget.h"
#include "Project1/UI/Inventory/InventoryWidget.h"

void UStoreMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_StoreWidget = Cast<UStoreWidget>(GetWidgetFromName(TEXT("UI_Store")));
	m_InventoryWidget = Cast<UInventoryWidget>(GetWidgetFromName(TEXT("UI_Inventory")));
	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	m_CloseButton->OnClicked.AddDynamic(this, &UStoreMainWidget::CloseButtonClicked);
}

void UStoreMainWidget::CloseButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}