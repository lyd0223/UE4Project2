#include "PreCompile.h"
#include "RequestCharacterInfoMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBCharacterInfoTable.h"
#include "GameServerMessage/ContentsStruct.h"

void RequestCharacterInfoMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("SignIn TCPSession is Nullptr");
		return;
	}

	DBQueue::EnQueue(std::bind(&RequestCharacterInfoMessageHandler::DBCheck, std::dynamic_pointer_cast<RequestCharacterInfoMessageHandler>(shared_from_this())));
}

void RequestCharacterInfoMessageHandler::DBCheck()
{
	DBCharacterInfoTable_SelectCharacterInfoQuery SelectQuery(m_Message->m_UserIdx);
	if (SelectQuery.DoQuery() == false)
	{
		//쿼리 실패. 바로 에러띄우고, 리턴때려버림.
		GameServerDebug::LogInfo("DBCharacterInfoTable_SelectCharacterInfoQuery Error");
		return;
	}

	for (auto& RowData : SelectQuery.m_RowDataList)
	{
		std::shared_ptr<FCharacterInfo> CharacterInfo = 
			std::make_shared<FCharacterInfo>(RowData->m_Idx, RowData->m_UserIdx, RowData->m_Nickname, RowData->m_ClassName,
				RowData->m_LV, RowData->m_EXP,
				RowData->m_HP, RowData->m_SP, RowData->m_ATK, RowData->m_DEF,
				RowData->m_AttackSpeed, RowData->m_MoveSpeed,
				RowData->m_InventoryData);
		m_ReplyCharacterInfoMessage.m_CharacterInfoList.push_back(*CharacterInfo);
	}

	NetQueue::EnQueue(std::bind(&RequestCharacterInfoMessageHandler::ResultSend, std::dynamic_pointer_cast<RequestCharacterInfoMessageHandler>(shared_from_this())));
}

void RequestCharacterInfoMessageHandler::ResultSend()
{
	GameServerSerializer Serializer;
	m_ReplyCharacterInfoMessage.Serialize(Serializer);

	m_TCPSession->Send(Serializer.GetData());

	GameServerDebug::LogInfo("ReplyCharacterInfoMessage Send");
}