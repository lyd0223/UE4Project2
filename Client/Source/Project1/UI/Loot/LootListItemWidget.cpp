// Fill out your copyright notice in the Description page of Project Settings.


#include "LootListItemWidget.h"

#include "LootListItemData.h"


void ULootListItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_BorderImage = Cast<UImage>(GetWidgetFromName(TEXT("BorderImage")));
	m_ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	m_CountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CountText")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_TypeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TypeText")));
}

void ULootListItemWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void ULootListItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	ULootListItemData* ListItem = Cast<ULootListItemData>(ListItemObject);
	
	ListItem->SetOwnerItemWidget(this);
	
	FItem* Item = ListItem->GetItem();
	
	m_ItemImage->SetBrushFromTexture(Item->ItemTableInfo->IconTexture);
	m_CountText->SetText(FText::FromString(FString::FromInt(Item->Count)));
	m_NameText->SetText(FText::FromString(Item->ItemTableInfo->Name));
	FString TypeString = "";
	switch (Item->ItemTableInfo->ItemType)
	{
	case EItemType::Equipment:
		TypeString = TEXT("Equipment");
		break;

	case EItemType::Uses_Buff :
			__fallthrough;
	case EItemType::Uses_Potion :
		TypeString = TEXT("Uses");
		break;
		
	case EItemType::Quest:
		TypeString = TEXT("Quest");
		break;
		
	case EItemType::Gold:
		TypeString = TEXT("Gold");
		break;
	}
	m_TypeText->SetText(FText::FromString(TypeString));
}


void ULootListItemWidget::Hovered()
{
	m_BorderImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void ULootListItemWidget::UnHovered()
{
	m_BorderImage->SetVisibility(ESlateVisibility::Collapsed);
}