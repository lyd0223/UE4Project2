#pragma once
#include "MessageHandlerBase.h"

/*
Usage		:
Category	:
Description :  채팅 패킷이 오면 처리해야할 동작을 구현.
*/

class ChatMessageHandler : public MessageHandlerBase<ChatMessage>
{
public:
	//메시지 받았을때 실행하는 함수.
	virtual void Start() override;

private:
	void ResultSend();

};