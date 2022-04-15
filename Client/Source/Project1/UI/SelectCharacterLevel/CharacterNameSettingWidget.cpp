// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterNameSettingWidget.h"

void UCharacterNameSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_CreateButton = Cast<UButton>(GetWidgetFromName(TEXT("CreateButton")));
	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	m_CreateButton->OnClicked.AddDynamic(this, &UCharacterNameSettingWidget::CreateButtonClicked);
	m_CloseButton->OnClicked.AddDynamic(this, &UCharacterNameSettingWidget::CloseButtonClicked);
	
	m_NameTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("NameTextBox")));
	m_NameString = TEXT("");
}

void UCharacterNameSettingWidget::CreateButtonClicked()
{
	
}

void UCharacterNameSettingWidget::CloseButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UCharacterNameSettingWidget::NameTextBoxChanged(const FText& Text)
{
	m_NameString = Text.ToString();
} 
