#include "ServerDestroyMessageHandler.h"

#include "Kismet/GameplayStatics.h"


ServerDestroyMessageHandler::ServerDestroyMessageHandler(std::shared_ptr<ServerDestroyMessage> _ServerDestroyMessage)
{
	m_ServerDestroyMessage = _ServerDestroyMessage;
}

void ServerDestroyMessageHandler::Init(UClientGameInstance* _GameInstance, UWorld* _World)
{
	m_GameInstance = _GameInstance;
	m_World = _World;
}

void ServerDestroyMessageHandler::Start()
{
	if(m_World->GetName() != TEXT("LoginLevel"))
	{
		UGameplayStatics::OpenLevel(m_World, TEXT("LoginLevel"));
	}
}


