// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameModeBase.h"
#include "UI/StartLevel/StartMainWidget.h"

AStartGameModeBase::AStartGameModeBase()
{
	static ConstructorHelpers::FClassFinder<UStartMainWidget>	StartHUDClass(TEXT("WidgetBlueprint'/Game/01Resources/UI/StartLevel/UI_StartMainWidget.UI_StartMainWidget_C'"));

	if (StartHUDClass.Succeeded())
		m_StartHUDClass = StartHUDClass.Class;
}

void AStartGameModeBase::InitGame(const FString& MapName,
	const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AStartGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_StartHUDClass))
	{
		m_StartHUD = Cast<UStartMainWidget>(CreateWidget(GetWorld(),
			m_StartHUDClass));

		if (m_StartHUD)
			m_StartHUD->AddToViewport();
	}

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	FInputModeUIOnly	Mode;
	Controller->SetInputMode(Mode);
	Controller->bShowMouseCursor = true;
}
