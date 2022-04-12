#include "PreCompile.h"
#include "RequestCharacterInfoMessageHandler.h"
#include <GameServerBase/GameServerDebug.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include "DBCharacterInfoTable.h"

RequestCharacterInfoMessageHandler::RequestCharacterInfoMessageHandler(std::shared_ptr<TCPSession> _TCPSession,
	std::shared_ptr<RequestCharacterInfoMessage> _RequestCharacterInfoMessage)
{
	m_TCPSession = _TCPSession;
	m_RequestCharacterInfoMessage = _RequestCharacterInfoMessage;
}

RequestCharacterInfoMessageHandler::~RequestCharacterInfoMessageHandler()
{

}

void RequestCharacterInfoMessageHandler::Start()
{
	if (m_TCPSession == nullptr)
	{
		GameServerDebug::LogError("SignIn TCPSession is Nullptr");
		return;
	}
	//m_RequestCharacterInfoMessage.m_SignInResultType = ESignInResultType::OK;

	DBQueue::EnQueue(std::bind(&RequestCharacterInfoMessageHandler::DBCheck, shared_from_this()));

}

void RequestCharacterInfoMessageHandler::DBCheck()
{
	//UserInfoTable_SelectIDQuery SelectQuery(m_SignInMessage->m_ID, m_SignInMessage->m_PW);
	//if (SelectQuery.DoQuery() == false)
	//{
	//	//���� ����. (ID ������������.)
	//	m_SignInResultMessage.m_SignInResultType = ESignInResultType::Error;
	//}
	//else
	//{
	//	if (SelectQuery.CheckPW() == false)
	//	{
	//		// ��й�ȣ Ʋ��. Ʋ�Ǵٴ� ��Ŷ ��������.
	//		m_SignInResultMessage.m_SignInResultType = ESignInResultType::Error;
	//	}
	//	else
	//	{
	//		m_SignInResultMessage.m_SignInResultType = ESignInResultType::OK;
	//		m_SignInResultMessage.m_UserIdx = SelectQuery.m_RowData->m_Index;
	//	}
	//}

	//NetQueue::EnQueue(std::bind(&SignInMessageHandler::ResultSend, shared_from_this()));
}

void RequestCharacterInfoMessageHandler::ResultSend()
{
	/*std::shared_ptr<GameServerUser> NewUser = std::make_shared<GameServerUser>();
	GameServerString::UTF8ToAnsi(m_SignInMessage->m_ID, NewUser->ID);

	m_TCPSession->SetLink(NewUser);*/

	GameServerSerializer Serializer;
	m_ReplyCharacterInfoMessage.Serialize(Serializer);

	m_TCPSession->Send(Serializer.GetData());

	GameServerDebug::LogInfo("ReplyCharacterInfoMessage Send");
}