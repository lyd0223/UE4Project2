#pragma once
#include "MessageHandlerBase.h"

/*
Usage		:
Category	:
Description :  ä�� ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class ChatMessageHandler : public MessageHandlerBase<ChatMessage>
{
public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	virtual void Start() override;

private:
	void ResultSend();

};