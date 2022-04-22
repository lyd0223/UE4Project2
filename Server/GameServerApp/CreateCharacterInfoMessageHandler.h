#pragma once
#include "MessageHandlerBase.h"

/*
Usage		:  MessageHandler
Category	:
Description :  CreateCharacterInfo 패킷이 오면 처리해야할 동작을 구현.
*/

class CreateCharacterInfoMessageHandler : public MessageHandlerBase<CreateCharacterInfoMessage>
{
protected:
	CreateCharacterInfoResultMessage m_CreateCharacterInfoResultMessage;

public:
	//메시지 받았을때 실행하는 함수.
	virtual void Start() override;

	void DBCheck();

private:
	void ResultSend();

};
