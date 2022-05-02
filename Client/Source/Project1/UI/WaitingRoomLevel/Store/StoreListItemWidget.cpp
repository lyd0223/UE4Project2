// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreListItemWidget.h"

#include "StoreListItemData.h"
#include "BuyWidget.h"
#include "StoreWidget.h"


void UStoreListItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_ItemImage =Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	m_BorderImage =Cast<UImage>(GetWidgetFromName(TEXT("BorderImage")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_CountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CountText")));
	m_GoldText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GoldText")));

	m_Item = nullptr;
	m_BuyWidget = nullptr;
}


void UStoreListItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UStoreListItemData* ListItem = Cast<UStoreListItemData>(ListItemObject);
	ListItem->SetOwnerWidget(this);
	m_BuyWidget = ListItem->GetStoreWidget()->GetBuyWidget();
	
	m_Item = ListItem->GetItem();
	m_ItemImage->SetBrushFromTexture(m_Item->ItemTableInfo->IconTexture);
	m_NameText->SetText(FText::FromString(m_Item->ItemTableInfo->Name));
	m_GoldText->SetText(FText::FromString(FString::FromInt(m_Item->ItemTableInfo->Price)));
}

void UStoreListItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	m_BorderImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}


void UStoreListItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	m_BorderImage->SetVisibility(ESlateVisibility::Collapsed);
	
}

FReply UStoreListItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	m_BuyWidget->OpenBuyWidget(m_Item);
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	return Reply.NativeReply;
}