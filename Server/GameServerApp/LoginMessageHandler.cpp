#include "PreCompile.h"
#include "LoginMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBUserInfoTable.h"

LoginMessageHandler::LoginMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<LoginMessage> _LoginMessage)
{
	m_TCPSession = _TCPSession;
	m_LoginMessage = _LoginMessage;
}

LoginMessageHandler::~LoginMessageHandler()
{

}

void LoginMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("Login TCPSession is Nullptr");
		return;
	}
	m_LoginResultMessage.m_LoginResultType = ELoginResultType::OK;

	DBQueue::EnQueue(std::bind(&LoginMessageHandler::DBCheck, shared_from_this()));
	
}

void LoginMessageHandler::DBCheck()
{
	std::string Name = GameServerThread::GetName();

	//UserInfoTable_SelectIDQuery SelectQuery(m_LoginMessage->m_ID);
	//SelectQuery.DoQuery();
	UserInfoTable_InsertUserInfoQuery InsertUserInfoQuery("111", "");
	InsertUserInfoQuery.DoQuery();

	//if (nullptr == SelectQuery.RowData)
	//{
	//	LoginResult_.Code = EGameServerCode::LoginError;
	//}
	//else
	//{
	//	LoginResult_.Code = EGameServerCode::OK;
	//}

	//UserTable_InsertUserInfo Query = UserTable_InsertUserInfo("kk", "kk");
	//if (false == Query.DoQuery())
	//{
	//	int a = 0;
	//}


	// INSERT INTO `userver2`.`user` (`ID`, `PW`) VALUES('c', 'c');

	NetQueue::EnQueue(std::bind(&LoginMessageHandler::ResultSend, shared_from_this()));
}

void LoginMessageHandler::ResultSend()
{
	/*std::shared_ptr<GameServerUser> NewUser = std::make_shared<GameServerUser>();
	GameServerString::UTF8ToAnsi(m_LoginMessage->m_ID, NewUser->ID);
	
	m_TCPSession->SetLink(NewUser);*/

	GameServerSerializer Serializer;
	m_LoginResultMessage.Serialize(Serializer);

	m_TCPSession->Send(Serializer.GetData());

	GameServerDebug::LogInfo("Login Result Send");
}