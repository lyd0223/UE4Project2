#pragma once
#include "MessageHandlerBase.h"

/*
Usage		:  MessageHandler
Category	:
Description :  DeleteCharacterInfo 패킷이 오면 처리해야할 동작을 구현.
*/

class DeleteCharacterInfoMessageHandler : public MessageHandlerBase<DeleteCharacterInfoMessage>
{
protected:
	DeleteCharacterInfoResultMessage m_ResultMessage;

public:
	//메시지 받았을때 실행하는 함수.
	virtual void Start() override;

	void DBCheck();

private:
	void ResultSend();

};