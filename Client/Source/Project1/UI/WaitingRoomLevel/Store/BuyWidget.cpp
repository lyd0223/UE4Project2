// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyWidget.h"

#include "Project1/Project1GameInstance.h"
#include "Project1/Manager/InventoryManager.h"


void UBuyWidget::NativeConstruct()
{
	m_ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_CountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CountText")));
	m_PriceText = Cast<UTextBlock>(GetWidgetFromName(TEXT("PriceText")));
	m_CountAdditionButton = Cast<UButton>(GetWidgetFromName(TEXT("CountAdditionButton")));
	m_CountSubtractionButton = Cast<UButton>(GetWidgetFromName(TEXT("CountSubtractionButton")));
	m_BuyButton = Cast<UButton>(GetWidgetFromName(TEXT("BuyButton")));
	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	m_CountAdditionButton->OnClicked.AddDynamic(this, &UBuyWidget::CountAdditionButtonClicked);
	m_CountSubtractionButton->OnClicked.AddDynamic(this, &UBuyWidget::CountSubtractionButtonClicked);
	m_BuyButton->OnClicked.AddDynamic(this, &UBuyWidget::BuyButtonClicked);
	m_CloseButton->OnClicked.AddDynamic(this, &UBuyWidget::CloseButtonClicked);
	
	m_Count = 0;
	m_Price = 0;
}

void UBuyWidget::OpenBuyWidget(FItem* Item)
{
	this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	m_Item = Item;
	m_ItemImage->SetBrushFromTexture(m_Item->ItemTableInfo->IconTexture);
	m_NameText->SetText(FText::FromString(m_Item->ItemTableInfo->Name));
	m_Count = 0;
	m_Price = 0;
	m_CountText->SetText(FText::FromString(FString::FromInt(m_Count)));
	m_PriceText->SetText(FText::FromString(FString::FromInt(m_Price)));
	
}

void UBuyWidget::CountAdditionButtonClicked()
{
	if(m_Item == nullptr)
		return;
	if(m_Count >= 99)
		return;
	
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetGameInstance());
	if(GameInstance == nullptr)
		return;
	UInventoryManager* InventoryManager = GameInstance->GetInventoryManager();
	if(InventoryManager->GetGold() == 0)
		return;
	int Price = m_Item->ItemTableInfo->Price * (m_Count + 1);
	if(InventoryManager->GetGold() < Price)
	{
		return;
	}
	m_Count++;
	m_CountText->SetText(FText::FromString(FString::FromInt(m_Count)));
	m_Price = Price;
	m_PriceText->SetText(FText::FromString(FString::FromInt(m_Price)));
}

void UBuyWidget::CountSubtractionButtonClicked()
{
	if(m_Item == nullptr)
    		return;
	if(m_Count <= 0)
		return;

	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetGameInstance());
	if(GameInstance == nullptr)
		return;
	UInventoryManager* InventoryManager = GameInstance->GetInventoryManager();
	if(InventoryManager->GetGold() == 0)
		return;
	int Price = m_Item->ItemTableInfo->Price * (m_Count - 1);
	m_Count--;
	m_CountText->SetText(FText::FromString(FString::FromInt(m_Count)));
	m_Price = Price;
	m_PriceText->SetText(FText::FromString(FString::FromInt(m_Price)));
}

void UBuyWidget::BuyButtonClicked()
{
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetGameInstance());
	if(GameInstance == nullptr)
		return;
	UInventoryManager* InventoryManager = GameInstance->GetInventoryManager();
	if(InventoryManager == nullptr)
		return;
	if(m_Item == nullptr)
		return;
	
	FItem* Item = new FItem;
	Item->ItemTableInfo = m_Item->ItemTableInfo;
	Item->Count = m_Count;
	InventoryManager->AddItem(Item);
	InventoryManager->DeductGold(m_Price);
	
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UBuyWidget::CloseButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}