#include "PreCompile.h"
#include "SignUpMessageHandler.h"


#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBUserInfoTable.h"

SignUpMessageHandler::SignUpMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<SignUpMessage> _SignUpMessage)
{
	m_TCPSession = _TCPSession;
	m_SignUpMessage = _SignUpMessage;
}

SignUpMessageHandler::~SignUpMessageHandler()
{

}

void SignUpMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("Login TCPSession is Nullptr");
		return;
	}
	m_SignUpResultMessage.m_SignUpResultType = ESignUpResultType::MAX;

	DBQueue::EnQueue(std::bind(&SignUpMessageHandler::DBCheck, shared_from_this()));

}

void SignUpMessageHandler::DBCheck()
{
	std::string Name = GameServerThread::GetName();
	
	UserInfoTable_InsertUserInfoQuery InsertUserInfoQuery(m_SignUpMessage->m_ID, m_SignUpMessage->m_PW);
	
	int CheckResult = InsertUserInfoQuery.DoQuery();
	m_SignUpResultMessage.m_SignUpResultType = CheckResult == true ? ESignUpResultType::OK : ESignUpResultType::Error_NonAvailableID;

	NetQueue::EnQueue(std::bind(&SignUpMessageHandler::ResultSend, shared_from_this()));
}

void SignUpMessageHandler::ResultSend()
{
	/*std::shared_ptr<GameServerUser> NewUser = std::make_shared<GameServerUser>();
	GameServerString::UTF8ToAnsi(m_LoginMessage->m_ID, NewUser->ID);

	m_TCPSession->SetLink(NewUser);*/

	GameServerSerializer Serializer;
	m_SignUpResultMessage.Serialize(Serializer);

	m_TCPSession->Send(Serializer.GetData());

	GameServerDebug::LogInfo("SignUp Result Send");
}