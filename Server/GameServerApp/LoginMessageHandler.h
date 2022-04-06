#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

/*
Usage		:  
Category	:  
Description :  �α��� ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class LoginMessageHandler final 
	: public std::enable_shared_from_this<LoginMessageHandler>
{
private:
	//��Ŷ�� ���� ����
	std::shared_ptr<TCPSession> m_TCPSession;
	
	//�� ��Ŷ
	std::shared_ptr<LoginMessage> m_LoginMessage;

	//��� ��Ŷ
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
	//�޽��� �޾����� �����ϴ� �Լ�.
	void Start();

private:
	void DBCheck();
	void ResultSend();
	
};

