#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

/*
Usage		:  
Category	:  
Description :  �α��� ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class SignInMessageHandler final 
	: public std::enable_shared_from_this<SignInMessageHandler>
{
private:
	//��Ŷ�� ���� ����
	std::shared_ptr<TCPSession> m_TCPSession;
	
	//�� ��Ŷ
	std::shared_ptr<SignInMessage> m_SignInMessage;

	//��� ��Ŷ
	SignInResultMessage m_SignInResultMessage;

public: //Default
	SignInMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<SignInMessage> _SignInMessage);
	~SignInMessageHandler();

	SignInMessageHandler(const SignInMessageHandler& _Other) = delete;
	SignInMessageHandler(SignInMessageHandler&& _Other)		noexcept = delete;
	SignInMessageHandler& operator=(const SignInMessageHandler& _Other) = delete;
	SignInMessageHandler& operator=(SignInMessageHandler&& _Other)		= delete;


public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	void Start();

private:
	void DBCheck();
	void ResultSend();
	
};

