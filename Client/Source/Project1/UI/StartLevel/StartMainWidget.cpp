// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMainWidget.h"
#include "SignUpWidget.h"

void UStartMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_SignInButton = Cast<UButton>(GetWidgetFromName(TEXT("SignInButton")));
	m_SignUpButton = Cast<UButton>(GetWidgetFromName(TEXT("SignUpButton")));
	m_QuitButton = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));
	m_SignUpWidget = Cast<USignUpWidget>(GetWidgetFromName(TEXT("UI_SignUpWidget")));
	
	m_SignInButton->OnClicked.AddDynamic(this, &UStartMainWidget::SignInButtonClicked);
	m_SignUpButton->OnClicked.AddDynamic(this, &UStartMainWidget::SignUpButtonClicked);
	m_QuitButton->OnClicked.AddDynamic(this, &UStartMainWidget::QuitButtonClicked);

}

void UStartMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UStartMainWidget::SignInButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("SelectCharacter"));
	// if(m_SignUpWidget->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)
	// 	m_SignUpWidget->SetVisibility(ESlateVisibility::Collapsed);
	// else
	// 	m_SignUpWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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
