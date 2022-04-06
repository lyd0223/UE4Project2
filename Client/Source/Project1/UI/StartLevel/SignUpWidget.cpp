// Fill out your copyright notice in the Description page of Project Settings.


#include "SignUpWidget.h"


void USignUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_SignUpButton = Cast<UButton>(GetWidgetFromName(TEXT("SignUpButton")));
	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	m_SignUpButton->OnClicked.AddDynamic(this, &USignUpWidget::SignUpButtonClicked);
	m_CloseButton->OnClicked.AddDynamic(this, &USignUpWidget::CloseButtonClicked);

	m_IDTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IDTextBox")));
	m_PWTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PWTextBox")));
	m_IDTextBox->OnTextChanged.AddDynamic(this, &USignUpWidget::IDTextBoxChanged);
	m_PWTextBox->OnTextChanged.AddDynamic(this, &USignUpWidget::PWTextBoxChanged);

	m_IDString = "";
	m_PWString = "";
}

void USignUpWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void USignUpWidget::SignUpButtonClicked()
{
	//서버로 회원가입 패킷 보내기.
		
}

void USignUpWidget::CloseButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void USignUpWidget::IDTextBoxChanged(const FText& Text)
{
	m_IDString = Text.ToString();
}

void USignUpWidget::PWTextBoxChanged(const FText& Text)
{
	m_PWString = Text.ToString();
}