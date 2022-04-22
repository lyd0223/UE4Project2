#pragma once
#include "MessageHandlerBase.h"

/*
Usage		:  MessageHandler
Category	:
Description :  CreateCharacterInfo ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class CreateCharacterInfoMessageHandler : public MessageHandlerBase<CreateCharacterInfoMessage>
{
protected:
	CreateCharacterInfoResultMessage m_CreateCharacterInfoResultMessage;

public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	virtual void Start() override;

	void DBCheck();

private:
	void ResultSend();

};
