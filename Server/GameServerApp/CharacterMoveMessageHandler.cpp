#include "PreCompile.h"
#include "CharacterMoveMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include "NetQueue.h"
#include <GameServerNet/TCPListener.h>

void CharacterMoveMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("CharacterMoveMessageHandler TCPSession is Nullptr");
		return;
	}

	NetQueue::EnQueue(std::bind(&CharacterMoveMessageHandler::ResultSend, std::dynamic_pointer_cast<CharacterMoveMessageHandler>(shared_from_this())));
}


void CharacterMoveMessageHandler::ResultSend()
{
	GameServerSerializer Serializer;
	m_Message->Serialize(Serializer);

	//m_TCPSession->Send(Serializer.GetData());
	TCPListener* Listener = m_TCPSession->GetParent<TCPListener>();
	if (Listener == nullptr)
	{
		GameServerDebug::LogInfo("CharacterMoveMessageHandler's Listener is Nullptr");
		return;
	}
	Listener->BroadCast(Serializer.GetData(), nullptr);

	GameServerDebug::LogInfo("CharacterMoveMessage Send");
}