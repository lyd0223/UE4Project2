#include "LoginResultMessageHandler.h"

#include "Kismet/GameplayStatics.h"


LoginResultMessageHandler::LoginResultMessageHandler(std::shared_ptr<LoginResultMessage> _LoginResultMessage)
{
	m_LoginResultMessage = _LoginResultMessage;
}

void LoginResultMessageHandler::Init(UClientGameInstance* _GameInstance, UWorld* _World)
{
	m_GameInstance = _GameInstance;
	m_World = _World;
}

void LoginResultMessageHandler::Start()
{
	if(m_LoginResultMessage->m_LoginResultType == ELoginResultType::OK)
	{
		UGameplayStatics::OpenLevel(m_World, TEXT("MainLevel"));
		
	}
}


