#pragma once

#include "MessageHandlerBase.h"

/*
Usage		:
Category	:
Description :  ȸ������ ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class SignUpMessageHandler : public MessageHandlerBase<SignUpMessage>
{
private:
	//��� ��Ŷ
	SignUpResultMessage m_SignUpResultMessage;

public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	virtual void Start() override;

private:
	void DBCheck();
	void ResultSend();

};

