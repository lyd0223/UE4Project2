#include "PreCompile.h"
#include "DeleteCharacterInfoMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBCharacterInfoTable.h"
#include "GameServerMessage/ContentsStruct.h"

void DeleteCharacterInfoMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("DeleteCharacterInfoMessageHandler TCPSession is Nullptr");
		return;
	}

	DBQueue::EnQueue(std::bind(&DeleteCharacterInfoMessageHandler::DBCheck, std::dynamic_pointer_cast<DeleteCharacterInfoMessageHandler>(shared_from_this())));
}

void DeleteCharacterInfoMessageHandler::DBCheck()
{
	FCharacterInfo& CharacterInfo = m_Message->m_CharacterInfo;

	DBCharacterInfoTable_DeleteCharacterInfoQuery DeleteQuery(CharacterInfo);
	if (DeleteQuery.DoQuery() == false)
	{
		//쿼리 실패. 바로 에러띄우고, 리턴때려버림.
		GameServerDebug::LogInfo("DBCharacterInfoTable_DeleteCharacterInfoQuery Error");
		return;
	}

	DBCharacterInfoTable_SelectCharacterInfoQuery SelectQuery(m_Message->m_CharacterInfo.m_UserIdx);
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
		m_ResultMessage.m_CharacterInfoList.push_back(*CharacterInfo);
	}


	NetQueue::EnQueue(std::bind(&DeleteCharacterInfoMessageHandler::ResultSend, std::dynamic_pointer_cast<DeleteCharacterInfoMessageHandler>(shared_from_this())));
}

void DeleteCharacterInfoMessageHandler::ResultSend()
{
	GameServerSerializer Serializer;
	m_ResultMessage.Serialize(Serializer);

	m_TCPSession->Send(Serializer.GetData());

	GameServerDebug::LogInfo("DeleteCharacterInfoResultMessage Send");
}