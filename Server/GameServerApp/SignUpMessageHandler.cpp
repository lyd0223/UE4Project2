#include "PreCompile.h"
#include "SignUpMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBUserInfoTable.h"


void SignUpMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("Login TCPSession is Nullptr");
		return;
	}
	m_SignUpResultMessage.m_SignUpResultType = ESignUpResultType::MAX;

	DBQueue::EnQueue(std::bind(&SignUpMessageHandler::DBCheck, std::dynamic_pointer_cast<SignUpMessageHandler>(shared_from_this())));

}

void SignUpMessageHandler::DBCheck()
{
	std::string Name = GameServerThread::GetName();
	
	UserInfoTable_InsertUserInfoQuery InsertUserInfoQuery(m_Message->m_ID, m_Message->m_PW);
	
	bool CheckResult = InsertUserInfoQuery.DoQuery();
	m_SignUpResultMessage.m_SignUpResultType = CheckResult == true ? ESignUpResultType::OK : ESignUpResultType::Error_DuplicateID;

	NetQueue::EnQueue(std::bind(&SignUpMessageHandler::ResultSend, std::dynamic_pointer_cast<SignUpMessageHandler>(shared_from_this())));
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