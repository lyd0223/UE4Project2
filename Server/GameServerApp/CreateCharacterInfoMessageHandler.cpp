#include "PreCompile.h"
#include "CreateCharacterInfoMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBCharacterInfoTable.h"
#include "GameServerMessage/ContentsStruct.h"

CreateCharacterInfoMessageHandler::CreateCharacterInfoMessageHandler(std::shared_ptr<TCPSession> _TCPSession,
	std::shared_ptr<CreateCharacterInfoMessage> _CreateCharacterInfoMessage)
{
	m_TCPSession = _TCPSession;
	m_CreateCharacterInfoMessage = _CreateCharacterInfoMessage;
}

CreateCharacterInfoMessageHandler::~CreateCharacterInfoMessageHandler()
{

}

void CreateCharacterInfoMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("SignIn TCPSession is Nullptr");
		return;
	}

	DBQueue::EnQueue(std::bind(&CreateCharacterInfoMessageHandler::DBCheck, shared_from_this()));
}

void CreateCharacterInfoMessageHandler::DBCheck()
{
	DBCharacterInfoTable_InsertCharacterInfoQuery InsertQuery(m_CreateCharacterInfoMessage->m_CharacterInfo.m_Nickname);
	if (InsertQuery.DoQuery() == false)
	{
		//쿼리 실패. 바로 에러띄우고, 리턴때려버림.
		GameServerDebug::LogInfo("DBCharacterInfoTable_SelectCharacterInfoQuery Error");
		return;
	}

	//for (auto& RowData : SelectQuery.m_RowDataList)
	//{
	//	std::shared_ptr<FCharacterInfo> CharacterInfo =
	//		std::make_shared<FCharacterInfo>(RowData->m_Idx, RowData->m_UserIndx, RowData->m_Nickname, RowData->m_ClassName, RowData->m_LV,
	//			RowData->m_HP, RowData->m_MP, RowData->m_ATK);
	//	m_ReplyCharacterInfoMessage.m_CharacterInfoList.push_back(*CharacterInfo);
	//}

	NetQueue::EnQueue(std::bind(&CreateCharacterInfoMessageHandler::ResultSend, shared_from_this()));
}

void CreateCharacterInfoMessageHandler::ResultSend()
{
	GameServerSerializer Serializer;
	m_CreateCharacterInfoResultMessage.Serialize(Serializer);

	m_TCPSession->Send(Serializer.GetData());

	GameServerDebug::LogInfo("CreateCharacterInfoResultMessage Send");
}