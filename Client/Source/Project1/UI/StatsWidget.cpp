// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsWidget.h"

void UStatsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_LVText = Cast<UTextBlock>(GetWidgetFromName(TEXT("LevelText")));
	m_HPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPText")));
	m_SPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SPText")));
	m_DEFText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DEFText")));
	m_ATKText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ATKText")));
	m_ATKSpeedText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ATKSpeedText")));
	
}

void UStatsWidget::SetDatas(FPlayerInfo& PlayerInfo)
{
	m_LVText->SetText(FText::FromString(FString::Printf(TEXT("LV : %d"),PlayerInfo.Level)));
	m_HPText->SetText(FText::FromString(FString::FromInt(PlayerInfo.HPMax)));
	m_SPText->SetText(FText::FromString(FString::FromInt(PlayerInfo.SPMax)));
	m_DEFText->SetText(FText::FromString(FString::FromInt(PlayerInfo.DEF)));
	m_ATKText->SetText(FText::FromString(FString::FromInt(PlayerInfo.ATK)));
	m_ATKSpeedText->SetText(FText::FromString(FString::FromInt(PlayerInfo.AttackSpeed)));
}