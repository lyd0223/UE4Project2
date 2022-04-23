#pragma once
#include "MessageHandlerBase.h"

/*
Usage		:
Category	:
Description :  CharacterMove ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class CharacterMoveMessageHandler : public MessageHandlerBase<CharacterMoveMessage>
{
public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	virtual void Start() override;

private:
	void ResultSend();

};