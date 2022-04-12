// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLevelPopUpWidget.h"


void UStartLevelPopUpWidget::NativeConstruct()
{
	
	Super::NativeConstruct();

	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	m_PopUpTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("PopUpTextBlock")));
	
	m_CloseButton->OnClicked.AddDynamic(this, &UStartLevelPopUpWidget::CloseButtonClicked);
}

void UStartLevelPopUpWidget::CloseButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UStartLevelPopUpWidget::SetPopUpText(const FString& _Text)
{
	m_PopUpTextBlock->SetText(FText::FromString(_Text));
}