// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerConnectInfoWidget.h"

#include "Project1/Project1GameInstance.h"


void UServerConnectInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_ConnectButton = Cast<UButton>(GetWidgetFromName(TEXT("ConnectButton")));
	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	m_ConnectButton->OnClicked.AddDynamic(this, &UServerConnectInfoWidget::ConnectButtonClicked);
	m_CloseButton->OnClicked.AddDynamic(this, &UServerConnectInfoWidget::CloseButtonClicked);
	
	m_IPTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IPTextBox")));
	m_PortTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PortTextBox")));
	m_IPTextBox->OnTextChanged.AddDynamic(this, &UServerConnectInfoWidget::IPTextBoxChanged);
	m_PortTextBox->OnTextChanged.AddDynamic(this, &UServerConnectInfoWidget::PortTextBoxChanged);

	m_IPString = "127.0.0.1";
	m_PortString = "30001";

	m_ConnectStatusImage = Cast<UImage>(GetWidgetFromName(TEXT("ConnectStatusImage")));
	m_ConnectStatusImage->Brush.TintColor = FLinearColor::Red;
	m_ConnectStatusText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ConnectStatusText")));
}

void UServerConnectInfoWidget::ConnectButtonClicked()
{
	//서버 커넥트 호출.
	UProject1GameInstance* GameInst = Cast<UProject1GameInstance>(GetGameInstance());
	if (false == GameInst->ServerConnect(m_IPString, m_PortString))
	{
		return;
	}

	m_ConnectStatusText->SetText(FText::FromString(TEXT("Connected")));
	m_ConnectStatusImage->Brush.TintColor = FLinearColor::Green;
}

void UServerConnectInfoWidget::CloseButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UServerConnectInfoWidget::IPTextBoxChanged(const FText& Text)
{
	m_IPString = Text.ToString();
} 

void UServerConnectInfoWidget::PortTextBoxChanged(const FText& Text)
{
	m_PortString = Text.ToString();
}