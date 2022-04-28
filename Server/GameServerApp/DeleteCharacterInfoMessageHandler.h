#pragma once
#include "MessageHandlerBase.h"

/*
Usage		:  MessageHandler
Category	:
Description :  DeleteCharacterInfo ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class DeleteCharacterInfoMessageHandler : public MessageHandlerBase<DeleteCharacterInfoMessage>
{
protected:
	DeleteCharacterInfoResultMessage m_ResultMessage;

public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	virtual void Start() override;

	void DBCheck();

private:
	void ResultSend();

};