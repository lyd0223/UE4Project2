#pragma once
#include "MessageHandlerBase.h"

/*
Usage		:
Category	:
Description :  CharacterMove 패킷이 오면 처리해야할 동작을 구현.
*/

class CharacterMoveMessageHandler : public MessageHandlerBase<CharacterMoveMessage>
{
public:
	//메시지 받았을때 실행하는 함수.
	virtual void Start() override;

private:
	void ResultSend();

};