#include "PreCompile.h"
#include "SaveCharacterInfoMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBCharacterInfoTable.h"

SaveCharacterInfoMessageHandler::SaveCharacterInfoMessageHandler(std::shared_ptr<TCPSession> _TCPSession, 
	std::shared_ptr<SaveCharacterInfoMessage> _SaveCharacterInfoMessage)
{
	m_TCPSession = _TCPSession;
	m_SaveCharacterInfoMessage = _SaveCharacterInfoMessage;
}

SaveCharacterInfoMessageHandler::~SaveCharacterInfoMessageHandler()
{

}

void SaveCharacterInfoMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("SignIn TCPSession is Nullptr");
		return;
	}

	DBQueue::EnQueue(std::bind(&SaveCharacterInfoMessageHandler::DBCheck, shared_from_this()));

}

void SaveCharacterInfoMessageHandler::DBCheck()
{
	std::string Name = GameServerThread::GetName();

	DBCharacterInfoTable_UpdateCharacterInfoQuery UpdateQuery(m_SaveCharacterInfoMessage->m_UserIdx, m_SaveCharacterInfoMessage->m_CharacterInfo);
	if (UpdateQuery.DoQuery() == false)
	{
		//쿼리 실패. (ID 존재하지않음.)
		return;
	}
	else
	{
		//쿼리 성공
		GameServerDebug::LogInfo("CharacterInfo Save Succeed");
		int a = 0;
	}

	//NetQueue::EnQueue(std::bind(&SignInMessageHandler::ResultSend, shared_from_this()));
}
//
//void SaveCharacterInfoMessageHandler::ResultSend()
//{
//	/*std::shared_ptr<GameServerUser> NewUser = std::make_shared<GameServerUser>();
//	GameServerString::UTF8ToAnsi(m_SignInMessage->m_ID, NewUser->ID);
//
//	m_TCPSession->SetLink(NewUser);*/
//
//	GameServerSerializer Serializer;
//	m_SignInResultMessage.Serialize(Serializer);
//
//	m_TCPSession->Send(Serializer.GetData());
//
//	GameServerDebug::LogInfo("SignIn Result Send");
//}