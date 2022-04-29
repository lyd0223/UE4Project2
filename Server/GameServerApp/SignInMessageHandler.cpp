#include "PreCompile.h"
#include "SignInMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include <GameServerBase/GameServerString.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBUserInfoTable.h"

void SignInMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("SignIn TCPSession is Nullptr");
		return;
	}
	m_SignInResultMessage.m_SignInResultType = ESignInResultType::OK;

	DBQueue::EnQueue(std::bind(&SignInMessageHandler::DBCheck, std::dynamic_pointer_cast<SignInMessageHandler>(shared_from_this())));
	
}

void SignInMessageHandler::DBCheck()
{
	std::string Name = GameServerThread::GetName();

	UserInfoTable_SelectIDQuery SelectQuery(m_Message->m_ID, m_Message->m_PW);
	if (SelectQuery.DoQuery() == false)
	{
		m_SignInResultMessage.m_SignInResultType = ESignInResultType::Error;
		
	}
	else
	{
		if (SelectQuery.CheckPW() == false)
		{
			// 비밀번호 틀림. 틀렷다는 패킷 보내주자.
			m_SignInResultMessage.m_SignInResultType = ESignInResultType::Failed_WrongPassword;
		}
		else
		{
			if (!SelectQuery.m_RowData)
			{
				//ID 존재하지않음.
				m_SignInResultMessage.m_SignInResultType = ESignInResultType::Failed_NoUser;
			}
			else
			{
				m_SignInResultMessage.m_SignInResultType = ESignInResultType::OK;
				m_SignInResultMessage.m_UserIdx = SelectQuery.m_RowData->m_Index;
			}
		}

	}

	NetQueue::EnQueue(std::bind(&SignInMessageHandler::ResultSend, std::dynamic_pointer_cast<SignInMessageHandler>(shared_from_this())));
}

void SignInMessageHandler::ResultSend()
{
	/*std::shared_ptr<GameServerUser> NewUser = std::make_shared<GameServerUser>();
	GameServerString::UTF8ToAnsi(m_SignInMessage->m_ID, NewUser->ID);
	
	m_TCPSession->SetLink(NewUser);*/

	GameServerSerializer Serializer;
	m_SignInResultMessage.Serialize(Serializer);

	m_TCPSession->Send(Serializer.GetData());

	GameServerDebug::LogInfo("SignIn Result Send");
}