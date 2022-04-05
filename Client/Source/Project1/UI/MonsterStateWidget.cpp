// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterStateWidget.h"


void UMonsterStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_HPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPText")));
	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	m_ATKText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ATKText")));
	m_DEFText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DEFText")));

	this->SetVisibility(ESlateVisibility::Collapsed);
	
	m_AccTime = 0.f;
	m_Time = 5.f;
}

void UMonsterStateWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	m_AccTime += GetWorld()->DeltaTimeSeconds;
	if(m_AccTime >=m_Time)
	{
		this->SetVisibility(ESlateVisibility::Collapsed);
		m_AccTime = 0.f;
	}
}


void UMonsterStateWidget::SetDatas(const FMonsterInfo& MonsterInfo)
{
	if(this->Visibility == ESlateVisibility::Collapsed)
		this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	m_NameText->SetText(FText::FromString(MonsterInfo.Name));
	int32 HP = MonsterInfo.HP;
	if(HP < 0)
		HP = 0;
	FString Str = FString::Printf(TEXT("%d / %d"),HP, MonsterInfo.HPMax);
	m_HPText->SetText(FText::FromString(Str));
	m_HPBar->SetPercent(MonsterInfo.HP / (float)MonsterInfo.HPMax);
	m_ATKText->SetText(FText::FromString(FString::Printf(TEXT("ATK : %d"),MonsterInfo.Attack)));
	m_DEFText->SetText(FText::FromString(FString::Printf(TEXT("DEF : %d"),MonsterInfo.Armor)));
}