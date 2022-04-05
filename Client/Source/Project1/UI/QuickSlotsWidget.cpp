// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotsWidget.h"
#include "QuickItemSlotWidget.h"
#include "QuickBulletSlotWidget.h"

void UQuickSlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for(int i = 0 ; i <4; i++)
	{
		UQuickBulletSlotWidget* QuickBulletSlotWidget = Cast<UQuickBulletSlotWidget>(GetWidgetFromName(FName(FString::Printf(TEXT("UI_QuickBulletSlot_%d"),i))));
		m_QuickBulletSlotWidgetArray.Add(QuickBulletSlotWidget);
	}
	for(int i = 0 ; i <5; i++)
	{
		UQuickItemSlotWidget* QuickItemSlotWidget = Cast<UQuickItemSlotWidget>(GetWidgetFromName(FName(FString::Printf(TEXT("UI_QuickItemSlot_%d"),i))));
		m_QuickItemSlotWidgetArray.Add(QuickItemSlotWidget);
	}
}

void UQuickSlotsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}


void UQuickSlotsWidget::QuickBulletSlotOn(bool IsOn)
{
	if(IsOn)
	{
		for(auto Widget : m_QuickBulletSlotWidgetArray)
		{
			//Widget->SelectImageOn();
		}
	}
	else
	{
		for(auto Widget : m_QuickBulletSlotWidgetArray)
		{
			//Widget->SelectImageOff();
		}
	}
}
void UQuickSlotsWidget::QuickItemSlotOn(bool IsOn)
{
	if(IsOn)
	{
		for(auto Widget : m_QuickItemSlotWidgetArray)
		{
			Widget->SelectImageOn();
		}
	}
	else
	{
		for(auto Widget : m_QuickItemSlotWidgetArray)
		{
			Widget->SelectImageOff();
		}
	}
}


void UQuickSlotsWidget::QuickBulletSlotChange(EQuickBulletSlotChangeType ChangeType, uint8 Index)
{
	
	switch(ChangeType)
	{
		case EQuickBulletSlotChangeType::Left:
			m_QuickBulletSlotWidgetArray[Index]->SelectOn(false);
			m_QuickBulletSlotWidgetArray[Index-1]->SelectOn(true);
			break;
		case EQuickBulletSlotChangeType::Right:
			m_QuickBulletSlotWidgetArray[Index]->SelectOn(false);
			m_QuickBulletSlotWidgetArray[Index+1]->SelectOn(true);
			break;
	}
}

void UQuickSlotsWidget::RefreshItems(FItem* Item)
{
	for(auto QuickItemSlot :m_QuickItemSlotWidgetArray)
	{
		if(QuickItemSlot->GetItem() == Item)
			QuickItemSlot->SlotRefresh(Item->Count);
	}
}