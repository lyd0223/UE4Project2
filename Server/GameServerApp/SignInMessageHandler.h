#pragma once
#include "MessageHandlerBase.h"

/*
Usage		:  
Category	:  
Description :  �α��� ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class SignInMessageHandler : public MessageHandlerBase<SignInMessage>
{
private:
	//��� ��Ŷ
	SignInResultMessage m_SignInResultMessage;

public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	virtual void Start() override;

private:
	void DBCheck();
	void ResultSend();
	
};

