// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemToolTipWidget.h"


void UItemToolTipWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_TypeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TypeText")));
	m_DescText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DescText")));
	m_OptionText = Cast<UTextBlock>(GetWidgetFromName(TEXT("OptionText")));
	m_PriceText = Cast<UTextBlock>(GetWidgetFromName(TEXT("PriceText")));
}

void UItemToolTipWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}


void UItemToolTipWidget::SetDatas(FItem& Item)
{
	m_ItemImage->SetBrushFromTexture(Item.ItemTableInfo->IconTexture);
	m_NameText->SetText(FText::FromString(Item.ItemTableInfo->Name));
	m_DescText->SetText(FText::FromString(Item.ItemTableInfo->Desc));

	FString String = TEXT("");
	switch (Item.ItemTableInfo->ItemType)
	{
		case EItemType::Equipment:
			String = TEXT("Equipment");
			break;

		case EItemType::Uses_Buff :
			__fallthrough;
		case EItemType::Uses_Potion :
			String = TEXT("Uses");
			m_OptionText->SetVisibility(ESlateVisibility::Collapsed);
			break;

		case EItemType::Quest :
			String = TEXT("Quest");
			break;
	}
	m_TypeText->SetText(FText::FromString(String));
	m_PriceText->SetText(FText::FromString(FString::FromInt(Item.ItemTableInfo->Price)));
}
