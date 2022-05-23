#include "PreCompile.h"
#include "SaveCharacterInfoMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBCharacterInfoTable.h"


void SaveCharacterInfoMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("SignIn TCPSession is Nullptr");
		return;
	}

	DBQueue::EnQueue(std::bind(&SaveCharacterInfoMessageHandler::DBCheck, std::dynamic_pointer_cast<SaveCharacterInfoMessageHandler>(shared_from_this())));
}

void SaveCharacterInfoMessageHandler::DBCheck()
{
	std::string Name = GameServerThread::GetName();

	DBCharacterInfoTable_UpdateCharacterInfoQuery UpdateQuery(m_Message->m_UserIdx, m_Message->m_CharacterInfo);
	if (UpdateQuery.DoQuery() == false)
	{
		//Äõ¸® ½ÇÆÐ. 
		GameServerDebug::LogInfo("CharacterInfo Save Failed");
		return;
	}
	else
	{
		//Äõ¸® ¼º°ø
		GameServerDebug::LogInfo("CharacterInfo Save Succeed");
		int a = 0;
	}

}