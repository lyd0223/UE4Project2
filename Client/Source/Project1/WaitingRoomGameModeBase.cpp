// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingRoomGameModeBase.h"

#include "Project1GameInstance.h"
#include "Player/PlayerCharacter.h"
#include "Player/WaitingRoomLevel/WaitingRoomPlayerController.h"
#include "UI/WaitingRoomLevel/WaitingRoomMainWidget.h"


AWaitingRoomGameModeBase::AWaitingRoomGameModeBase()
{
	//캐릭터
	static ConstructorHelpers::FClassFinder<APawn>	GunnerClass(TEXT("Blueprint'/Game/01Resources/Player/Gunner/BPGunner.BPGunner_C'"));
	if (GunnerClass.Succeeded())
		m_PlayerClassArray.Add(GunnerClass.Class);

	static ConstructorHelpers::FClassFinder<APawn>	BelicaClass(TEXT("Blueprint'/Game/01Resources/Player/Belica/BPBelica.BPBelica_C'"));
	if (BelicaClass.Succeeded())
		m_PlayerClassArray.Add(BelicaClass.Class);

	static ConstructorHelpers::FClassFinder<APawn>	RevenantClass(TEXT("Blueprint'/Game/01Resources/Player/Gunner/BPGunner.BPGunner_C'"));
	if (RevenantClass.Succeeded())
		m_PlayerClassArray.Add(RevenantClass.Class);
	
	PlayerControllerClass = AWaitingRoomPlayerController::StaticClass();

	//UI
	static ConstructorHelpers::FClassFinder<UWaitingRoomMainWidget>
		WidgetClass(TEXT("WidgetBlueprint'/Game/01Resources/UI/WaitingRoomLevel/UI_WaitingRoomMain.UI_WaitingRoomMain_C'"));
	if (WidgetClass.Succeeded())
		m_MainWidgetClass = WidgetClass.Class;
	
}

void AWaitingRoomGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(m_MainWidgetClass))
	{
		m_MainWidget = Cast<UWaitingRoomMainWidget>(CreateWidget(GetWorld(), m_MainWidgetClass));

		if (m_MainWidget)
			m_MainWidget->AddToViewport();
			
		m_MainWidget->SetVisibility(ESlateVisibility::Collapsed);
	}


}


void AWaitingRoomGameModeBase::InitGame(const FString& MapName,
	const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//직업에 따른 캐릭터설정.
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetGameInstance());
	EPlayerJob Job = GameInstance->GetSelectJob();
	switch(Job)
	{
		case EPlayerJob::Gunner:
			DefaultPawnClass = m_PlayerClassArray[0];
			break;
		case EPlayerJob::Belica:
			DefaultPawnClass = m_PlayerClassArray[1];

			break;
		case EPlayerJob::Revenant:
			DefaultPawnClass = m_PlayerClassArray[2];

			break;
		case EPlayerJob::Wraith:

			break;
		case EPlayerJob::TwinBlaster:

			break;
		
	}
}
