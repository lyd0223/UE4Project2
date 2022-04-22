#pragma once

#include "MessageHandlerBase.h"

/*
Usage		:
Category	:
Description :  회원가입 패킷이 오면 처리해야할 동작을 구현.
*/

class SignUpMessageHandler : public MessageHandlerBase<SignUpMessage>
{
private:
	//결과 패킷
	SignUpResultMessage m_SignUpResultMessage;

public:
	//메시지 받았을때 실행하는 함수.
	virtual void Start() override;

private:
	void DBCheck();
	void ResultSend();

};

