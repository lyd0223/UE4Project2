// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectCharacterGameModeBase.h"

#include "Project1GameInstance.h"
#include "Player/SelectCharacterPlayerController.h"
#include "Player/SelectCharacterLevel/SelectDefaultPawn.h"
#include "UI/SelectCharacterLevel/SelectCharacterMainWidget.h"
#include <string>

#include "Global/Message/ClientToServer.h"

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

	//서버로 캐릭터인포 요청 패킷 보내기.--------------------------------------------------------
	UProject1GameInstance* GameInst = Cast<UProject1GameInstance>(GetGameInstance());
	if(GameInst->GetIsClientMode())
		return;		
	RequestCharacterInfoMessage Message;
	Message.m_UserIdx = GameInst->GetUserIdx(); 
	
	GameServerSerializer Serializer;
	Message.Serialize(Serializer);
	
	if (!GameInst->Send(Serializer.GetData()))
	{
		PrintViewport(2.f, FColor::Red, TEXT("RequestCharacterInfoMessage Send Error!"));
	}
	//--------------------------------------------------------------------------------------
	
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
