// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameModeBase.h"
#include "UI/StartLevel/StartMainWidget.h"

AStartGameModeBase::AStartGameModeBase()
{
	static ConstructorHelpers::FClassFinder<UStartMainWidget>	StartMainWidgetClass(TEXT("WidgetBlueprint'/Game/01Resources/UI/StartLevel/UI_StartMainWidget.UI_StartMainWidget_C'"));

	if (StartMainWidgetClass.Succeeded())
		m_StartMainWidgetClass = StartMainWidgetClass.Class;
}

void AStartGameModeBase::InitGame(const FString& MapName,
	const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AStartGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_StartMainWidgetClass))
	{
		m_StartMainWidget = Cast<UStartMainWidget>(CreateWidget(GetWorld(),
			m_StartMainWidgetClass));

		if (m_StartMainWidget)
			m_StartMainWidget->AddToViewport();
	}

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	FInputModeUIOnly	Mode;
	Controller->SetInputMode(Mode);
	Controller->bShowMouseCursor = true;
}
