// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuCommonWidget.h"
#include "QuickSlotsWidget.h"
#include "StatsWidget.h"

void UMenuCommonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_StatsWidget = Cast<UStatsWidget>(GetWidgetFromName(TEXT("UI_Stats")));
	
}

void UMenuCommonWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}
