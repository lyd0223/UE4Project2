#pragma once
#include "MessageHandlerBase.h"

/*
Usage		:  
Category	:  
Description :  로그인 패킷이 오면 처리해야할 동작을 구현.
*/

class SignInMessageHandler : public MessageHandlerBase<SignInMessage>
{
private:
	//결과 패킷
	SignInResultMessage m_SignInResultMessage;

public:
	//메시지 받았을때 실행하는 함수.
	virtual void Start() override;

private:
	void DBCheck();
	void ResultSend();
	
};

