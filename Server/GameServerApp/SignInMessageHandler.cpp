#include "PreCompile.h"
#include "SignInMessageHandler.h"


#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBUserInfoTable.h"

SignInMessageHandler::SignInMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<SignInMessage> _SignInMessage)
{
	m_TCPSession = _TCPSession;
	m_SignInMessage = _SignInMessage;
}

SignInMessageHandler::~SignInMessageHandler()
{

}

void SignInMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("Login TCPSession is Nullptr");
		return;
	}
	m_SignInResultMessage.m_SignInResultType = ESignInResultType::MAX;

	DBQueue::EnQueue(std::bind(&SignInMessageHandler::DBCheck, shared_from_this()));

}

void SignInMessageHandler::DBCheck()
{
	std::string Name = GameServerThread::GetName();
	
	UserInfoTable_InsertUserInfoQuery InsertUserInfoQuery(m_SignInMessage->m_ID, m_SignInMessage->m_PW);
	
	int CheckResult = InsertUserInfoQuery.DoQuery();
	m_SignInResultMessage.m_SignInResultType = CheckResult == true ? ESignInResultType::OK : ESignInResultType::Error_NonAvailableID;

	NetQueue::EnQueue(std::bind(&SignInMessageHandler::ResultSend, shared_from_this()));
}

void SignInMessageHandler::ResultSend()
{
	/*std::shared_ptr<GameServerUser> NewUser = std::make_shared<GameServerUser>();
	GameServerString::UTF8ToAnsi(m_LoginMessage->m_ID, NewUser->ID);

	m_TCPSession->SetLink(NewUser);*/

	GameServerSerializer Serializer;
	m_SignInResultMessage.Serialize(Serializer);

	m_TCPSession->Send(Serializer.GetData());

	GameServerDebug::LogInfo("SignIn Result Send");
}