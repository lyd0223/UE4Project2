#pragma once

#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

/*
Usage		:
Category	:
Description :  회원가입 패킷이 오면 처리해야할 동작을 구현.
*/

class SignUpMessageHandler final
	: public std::enable_shared_from_this<SignUpMessageHandler>
{
private:
	//패킷을 보낸 세션
	std::shared_ptr<TCPSession> m_TCPSession;

	//온 패킷
	std::shared_ptr<SignUpMessage> m_SignUpMessage;

	//결과 패킷
	SignUpResultMessage m_SignUpResultMessage;

public: //Default
	SignUpMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<SignUpMessage> _SignUpMessage);
	~SignUpMessageHandler();

	SignUpMessageHandler(const SignUpMessageHandler& _Other) = delete;
	SignUpMessageHandler(SignUpMessageHandler&& _Other)		noexcept = delete;

	SignUpMessageHandler& operator=(const SignUpMessageHandler& _Other) = delete;
	SignUpMessageHandler& operator=(SignUpMessageHandler&& _Other) = delete;


public:
	//메시지 받았을때 실행하는 함수.
	void Start();

private:
	void DBCheck();
	void ResultSend();

};

