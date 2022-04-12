// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMainWidget.h"
#include "SignUpWidget.h"
#include "SignInWidget.h"
#include "ServerConnectInfoWidget.h"
#include "Project1/Project1GameInstance.h"
#include <string>

#include "Project1/Global/ClientBlueprintFunctionLibrary.h"

void UStartMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_SignInButton = Cast<UButton>(GetWidgetFromName(TEXT("SignInButton")));
	m_SignUpButton = Cast<UButton>(GetWidgetFromName(TEXT("SignUpButton")));
	m_QuitButton = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));
	m_ServerConnectInfoButton = Cast<UButton>(GetWidgetFromName(TEXT("ServerConnectInfoButton")));
	m_SignUpWidget = Cast<USignUpWidget>(GetWidgetFromName(TEXT("UI_SignUpWidget")));
	m_SignInWidget = Cast<USignInWidget>(GetWidgetFromName(TEXT("UI_SignInWidget")));
	m_ServerConnectInfoWidget = Cast<UServerConnectInfoWidget>(GetWidgetFromName(TEXT("UI_ServerConnectInfoWidget")));
	
	m_SignInButton->OnClicked.AddDynamic(this, &UStartMainWidget::SignInButtonClicked);
	m_SignUpButton->OnClicked.AddDynamic(this, &UStartMainWidget::SignUpButtonClicked);
	m_QuitButton->OnClicked.AddDynamic(this, &UStartMainWidget::QuitButtonClicked);
	m_ServerConnectInfoButton->OnClicked.AddDynamic(this, &UStartMainWidget::ServerConnectInfoButtonClicked);

}

void UStartMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UStartMainWidget::SignInButtonClicked()
{
	if(m_SignInWidget->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
		m_SignInWidget->SetVisibility(ESlateVisibility::Collapsed);
	else
		m_SignInWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UStartMainWidget::SignUpButtonClicked()
{
	if(m_SignUpWidget->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
		m_SignUpWidget->SetVisibility(ESlateVisibility::Collapsed);
	else
		m_SignUpWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		
}

void UStartMainWidget::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}



void UStartMainWidget::ServerConnectInfoButtonClicked()
{
	if(m_ServerConnectInfoWidget->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
		m_ServerConnectInfoWidget->SetVisibility(ESlateVisibility::Collapsed);
	else
		m_ServerConnectInfoWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		
}