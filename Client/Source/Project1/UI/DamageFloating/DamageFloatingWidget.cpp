// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageFloatingWidget.h"


void UDamageFloatingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageText")));
	m_Opacity = 1.f;
}

void UDamageFloatingWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	m_Opacity -= 1.f * GetWorld()->DeltaTimeSeconds;
	m_DamageText->SetColorAndOpacity(FLinearColor(1.f,0.f,0.f,m_Opacity));

	if(m_Opacity <= 0.f)
	{
		m_OwnerActor->Destroy();
	}
}
