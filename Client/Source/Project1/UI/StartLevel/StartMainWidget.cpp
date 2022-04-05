// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMainWidget.h"
#include "LoadWidget.h"

void UStartMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	m_LoadButton = Cast<UButton>(GetWidgetFromName(TEXT("LoadButton")));
	m_QuitButton = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));
	m_LoadWidget = Cast<ULoadWidget>(GetWidgetFromName(TEXT("UI_LoadWidget")));
	
	m_StartButton->OnClicked.AddDynamic(this, &UStartMainWidget::StartButton);
	m_LoadButton->OnClicked.AddDynamic(this, &UStartMainWidget::LoadButton);
	m_QuitButton->OnClicked.AddDynamic(this, &UStartMainWidget::QuitButton);

}

void UStartMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UStartMainWidget::StartButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("SelectCharacter"));
}

void UStartMainWidget::LoadButton()
{
	if(m_LoadWidget->GetVisibility() == ESlateVisibility::HitTestInvisible)
		m_LoadWidget->SetVisibility(ESlateVisibility::Collapsed);
	else
		m_LoadWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		
}

void UStartMainWidget::QuitButton()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, true);
}
