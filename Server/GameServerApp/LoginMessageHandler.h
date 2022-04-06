#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

/*
Usage		:  
Category	:  
Description :  로그인 패킷이 오면 처리해야할 동작을 구현.
*/

class LoginMessageHandler final 
	: public std::enable_shared_from_this<LoginMessageHandler>
{
private:
	//패킷을 보낸 세션
	std::shared_ptr<TCPSession> m_TCPSession;
	
	//온 패킷
	std::shared_ptr<LoginMessage> m_LoginMessage;

	//결과 패킷
	LoginResultMessage m_LoginResultMessage;

public: //Default
	LoginMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<LoginMessage> _LoginMessage);
	~LoginMessageHandler();

	LoginMessageHandler(const LoginMessageHandler& _Other) = delete;
	LoginMessageHandler(LoginMessageHandler&& _Other)		noexcept = delete;

protected:
	LoginMessageHandler& operator=(const LoginMessageHandler& _Other) = delete;
	LoginMessageHandler& operator=(LoginMessageHandler&& _Other)		= delete;


public:
	//메시지 받았을때 실행하는 함수.
	void Start();

private:
	void DBCheck();
	void ResultSend();
	
};

