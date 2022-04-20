
#include "PreCompile.h"
#include "ChatMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include "NetQueue.h"
#include <GameServerNet/TCPListener.h>

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
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("ChatMessageHandler TCPSession is Nullptr");
		return;
	}
	
	NetQueue::EnQueue(std::bind(&ChatMessageHandler::ResultSend, shared_from_this()));
}


void ChatMessageHandler::ResultSend()
{
	GameServerSerializer Serializer;
	m_ChatMessage->Serialize(Serializer);
	
	//m_TCPSession->Send(Serializer.GetData());
	TCPListener* Listener = m_TCPSession->GetParent<TCPListener>();
	if (Listener == nullptr)
	{
		GameServerDebug::LogInfo("ChatMessageHandler's Listener is Nullptr");
		return;
	}
	Listener->BroadCast(Serializer.GetData(), nullptr);

	GameServerDebug::LogInfo("ChatMessage Send");
}