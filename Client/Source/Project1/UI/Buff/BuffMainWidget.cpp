// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffMainWidget.h"
#include "BuffSlotWidget.h"


void UBuffMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_PlayerCharacter = nullptr;	
	for(int i = 0; i <7; i++)
	{
		UBuffSlotWidget* SlotWidget = Cast<UBuffSlotWidget>(GetWidgetFromName(FName(FString::Printf(TEXT("UI_BuffSlot_%d"),i))));
		m_BuffSlotWidgetArray.Add(SlotWidget);
		SlotWidget->SetOwnerBuffMainWidget(this);
	}
}

void UBuffMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UBuffMainWidget::AddBuff(const FItemTableInfo* ItemTableInfo, float Duration)
{
	for(auto BuffWidget : m_BuffSlotWidgetArray)
	{
		bool IsActive = BuffWidget->GetIsActive();
		if(!IsActive)
		{
			BuffWidget->BuffStart(ItemTableInfo, Duration);
			break;
		}
		else
		{
			if(BuffWidget->GetItemTableInfo() == ItemTableInfo)
			{
				// 버프아이템이 이미 사용되어있다면
				// 있던버프제거하고 새로 켜준다.
				BuffWidget->BuffEnd();
				AddBuff(ItemTableInfo, Duration);
				break;
			}
		}
	}
}


void UBuffMainWidget::BuffRefresh(uint8 StartIndex)
{
	for(int i = StartIndex; i < 6; i++)
	{
		if(m_BuffSlotWidgetArray[i+1]->GetIsActive())
		{
			m_BuffSlotWidgetArray[i]->BuffSlotChange(m_BuffSlotWidgetArray[i+1]);
		}
		else
			break;
	}
}