#include "ChatMessageHandler.h"

#include "Kismet/GameplayStatics.h"


ChatMessageHandler::ChatMessageHandler(std::shared_ptr<ChatMessage> _ChatMessage)
{
	m_ChatMessage = _ChatMessage;
}

void ChatMessageHandler::Init(UClientGameInstance* _GameInstance, UWorld* _World)
{
	m_GameInstance = _GameInstance;
	m_World = _World;
}

void ChatMessageHandler::Start()
{
	
}


