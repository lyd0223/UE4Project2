// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacterGameModeBase.h"
#include "Player/SelectCharacterPlayerController.h"
#include "Player/SelectCharacterLevel/SelectDefaultPawn.h"
#include "UI/SelectCharacterLevel/SelectCharacterMainWidget.h"

ASelectCharacterGameModeBase::ASelectCharacterGameModeBase()
{
	PlayerControllerClass = ASelectCharacterPlayerController::StaticClass();
	DefaultPawnClass = ASelectDefaultPawn::StaticClass();

	static ConstructorHelpers::FClassFinder<USelectCharacterMainWidget>	SelectCharacterMainWidgetClass(TEXT("WidgetBlueprint'/Game/01Resources/UI/SelectCharacterLevel/UI_SelectCharacterMainWidget.UI_SelectCharacterMainWidget_C'"));
	if (SelectCharacterMainWidgetClass.Succeeded())
		m_SelectCharacterMainWidgetClass = SelectCharacterMainWidgetClass.Class;
	
	
}

void ASelectCharacterGameModeBase::InitGame(const FString& MapName,
	const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ASelectCharacterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_SelectCharacterMainWidgetClass))
	{
		m_SelectCharacterMainWidget = Cast<USelectCharacterMainWidget>(CreateWidget(GetWorld(),
			m_SelectCharacterMainWidgetClass));

		if (m_SelectCharacterMainWidget)
			m_SelectCharacterMainWidget->AddToViewport();
			
		m_SelectCharacterMainWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	
	FInputModeGameAndUI	Mode;

	Controller->SetInputMode(Mode);
	Controller->bShowMouseCursor = true;
}
