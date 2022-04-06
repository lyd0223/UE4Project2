
#include "PreCompile.h"
#include "ChatMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>

ChatMessageHandler::ChatMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<ChatMessage> _ChatMessage)
{
	m_TCPSession = _TCPSession;
	m_ChatMessage = _ChatMessage;
}

ChatMessageHandler::~ChatMessageHandler()
{

}

void ChatMessageHandler::Start()
{
	
	
}


void ChatMessageHandler::ResultSend()
{

}