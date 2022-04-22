#pragma once
#include "MessageHandlerBase.h"
/*
Usage		:  MessageHandler
Category	:
Description :  RequestCharacterInfo ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class RequestCharacterInfoMessageHandler : public MessageHandlerBase<RequestCharacterInfoMessage>
{
private:
	ReplyCharacterInfoMessage m_ReplyCharacterInfoMessage;

public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	virtual void Start() override;

	void DBCheck();

private:
	void ResultSend();

};