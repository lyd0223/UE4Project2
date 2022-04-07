#pragma once

#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

/*
Usage		:
Category	:
Description :  ȸ������ ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class SignUpMessageHandler final
	: public std::enable_shared_from_this<SignUpMessageHandler>
{
private:
	//��Ŷ�� ���� ����
	std::shared_ptr<TCPSession> m_TCPSession;

	//�� ��Ŷ
	std::shared_ptr<SignUpMessage> m_SignUpMessage;

	//��� ��Ŷ
	SignUpResultMessage m_SignUpResultMessage;

public: //Default
	SignUpMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<SignUpMessage> _SignUpMessage);
	~SignUpMessageHandler();

	SignUpMessageHandler(const SignUpMessageHandler& _Other) = delete;
	SignUpMessageHandler(SignUpMessageHandler&& _Other)		noexcept = delete;

	SignUpMessageHandler& operator=(const SignUpMessageHandler& _Other) = delete;
	SignUpMessageHandler& operator=(SignUpMessageHandler&& _Other) = delete;


public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	void Start();

private:
	void DBCheck();
	void ResultSend();

};

