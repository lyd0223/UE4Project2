// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickBulletSlotWidget.h"


void UQuickBulletSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_BulletImage = Cast<UImage>(GetWidgetFromName(TEXT("BulletImage")));
	m_SelectCanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("SelectCanvasPanel")));
	m_SlotButton = Cast<UButton>(GetWidgetFromName(TEXT("SlotButton")));
	
	if(!m_IsSelected)
	{
		m_SelectCanvasPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	
}

void UQuickBulletSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}


void UQuickBulletSlotWidget::SelectOn(bool IsOn)
{
	if(IsOn)
	{
		m_IsSelected = true;
		m_SelectCanvasPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		m_IsSelected = false;
		m_SelectCanvasPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
}