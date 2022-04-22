#include "PreCompile.h"
#include "CreateCharacterInfoMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBCharacterInfoTable.h"
#include "GameServerMessage/ContentsStruct.h"

void CreateCharacterInfoMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("SignIn TCPSession is Nullptr");
		return;
	}

	DBQueue::EnQueue(std::bind(&CreateCharacterInfoMessageHandler::DBCheck, std::dynamic_pointer_cast<CreateCharacterInfoMessageHandler>(shared_from_this())));
}

void CreateCharacterInfoMessageHandler::DBCheck()
{
	FCharacterInfo& CharacterInfo = m_Message->m_CharacterInfo;
	DBCharacterInfoTable_InsertCharacterInfoQuery InsertQuery(
		CharacterInfo.m_UserIdx, CharacterInfo);
	if (InsertQuery.DoQuery() == false)
	{
		//쿼리 실패. 바로 에러띄우고, 리턴때려버림.
		GameServerDebug::LogInfo("DBCharacterInfoTable_SelectCharacterInfoQuery Error");
		return;
	}

	m_CreateCharacterInfoResultMessage.m_CharacterInfo = m_Message->m_CharacterInfo;

	NetQueue::EnQueue(std::bind(&CreateCharacterInfoMessageHandler::ResultSend, std::dynamic_pointer_cast<CreateCharacterInfoMessageHandler>(shared_from_this())));
}

void CreateCharacterInfoMessageHandler::ResultSend()
{
	GameServerSerializer Serializer;
	m_CreateCharacterInfoResultMessage.Serialize(Serializer);

	m_TCPSession->Send(Serializer.GetData());

	GameServerDebug::LogInfo("CreateCharacterInfoResultMessage Send");
}