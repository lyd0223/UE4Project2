// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "InventorySlotWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/GridSlot.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Manager/InventoryManager.h"
#include "Project1/UI/Inventory/ItemToolTipWidget.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UInventorySlotWidget> InventorySlotWidgetClass(
		TEXT("WidgetBlueprint'/Game/01Resources/UI/Inventory/UI_InventorySlot.UI_InventorySlot_C'"));
	if (InventorySlotWidgetClass.Succeeded())
		m_InventorySlotWidgetClass = InventorySlotWidgetClass.Class;
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_GoldText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GoldText")));
	m_WeightText = Cast<UTextBlock>(GetWidgetFromName(TEXT("WeightText")));
	m_InventoryPanel = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("InventoryPanel")));
	m_ItemToolTipWidget = Cast<UItemToolTipWidget>(GetWidgetFromName(TEXT("UI_ItemToolTip")));

	for (int32 i = 0; i < 36; i++)
		AddInventorySlot();
}

void UInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryWidget::Refresh(TArray<FItem*>& ItemArray)
{
	for (int32 i = 0; i < ItemArray.Num(); i++)
	{
		UInventorySlotWidget* InventorySlotWidget = Cast<UInventorySlotWidget>(m_InventoryPanel->GetChildAt(i));
		
		InventorySlotWidget->SetDatas(ItemArray[i]);
	}
}

void UInventoryWidget::AddInventorySlot()
{
	UInventorySlotWidget* InventorySlotWidget = WidgetTree->ConstructWidget<UInventorySlotWidget>(
		m_InventorySlotWidgetClass);
	InventorySlotWidget->SetItemToolTipWidget(m_ItemToolTipWidget);
	InventorySlotWidget->SetOwnerWidget(this);
	int32 Row = m_InventoryPanel->GetChildrenCount() / 6;
	int32 Col = m_InventoryPanel->GetChildrenCount() % 6;
	m_InventoryPanel->AddChildToUniformGrid(InventorySlotWidget, Row, Col);

	m_SlotArray.Add(InventorySlotWidget);
}

void UInventoryWidget::AddItem(FItem* Item)
{
	//?????? ????????? ???????????? ????????????
	UInventorySlotWidget* InventorySlotWidget = nullptr;
	for (auto InventorySlot : m_SlotArray)
	{
		if (InventorySlot->GetItem() == nullptr)
		{
			//??????????????? ???????????????????????? ????????? ????????????.
			InventorySlotWidget = InventorySlot;
			break;
		}
		FItem* MyItem = InventorySlot->GetItem();
		if (MyItem == Item)
		{
			InventorySlot->SetDatas(Item);
			return;
		}
	}

	//???????????? ????????? ??????????????? ??? ???????????? ???????????????, ??? ??? ??? ????????? ????????????.
	if (InventorySlotWidget)
	{
		InventorySlotWidget->SetDatas(Item);
	}
}

void UInventoryWidget::DeductItemCount(FItem* Item)
{
	for (auto InventorySlot : m_SlotArray)
	{
		if (InventorySlot->GetItem() == Item)
		{
			InventorySlot->SetDatas(Item);

			if (Item->Count == 0)
			{
				//????????? ???????????? ?????? ???????????? ??? ?????????.
			}
			break;
		}
	}
}

void UInventoryWidget::SetGoldText(uint64 _Gold)
{
	m_GoldText->SetText(FText::FromString(FString::Printf(TEXT("%lld"),_Gold)));
}

void UInventoryWidget::SetWeightText(uint8 _NowWeigth, uint8 _MaxWeight)
{
	m_WeightText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"),_NowWeigth, _MaxWeight)));
}
