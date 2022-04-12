#pragma once

#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

/*
Usage		:  MessageHandler
Category	:
Description :  RequestCharacterInfo ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class RequestCharacterInfoMessageHandler final
	: public std::enable_shared_from_this<RequestCharacterInfoMessageHandler>
{
private:
	//��Ŷ�� ���� ����
	std::shared_ptr<TCPSession> m_TCPSession;

	//�� ��Ŷ
	std::shared_ptr<RequestCharacterInfoMessage> m_RequestCharacterInfoMessage;

	ReplyCharacterInfoMessage m_ReplyCharacterInfoMessage;

public: //Default
	RequestCharacterInfoMessageHandler(std::shared_ptr<TCPSession> _TCPSession,
		std::shared_ptr<RequestCharacterInfoMessage> _RequestCharacterInfoMessage);
	~RequestCharacterInfoMessageHandler();

	RequestCharacterInfoMessageHandler(const RequestCharacterInfoMessageHandler& _Other) = delete;
	RequestCharacterInfoMessageHandler(RequestCharacterInfoMessageHandler&& _Other)		noexcept = delete;
	RequestCharacterInfoMessageHandler& operator=(const RequestCharacterInfoMessageHandler& _Other) = delete;
	RequestCharacterInfoMessageHandler& operator=(RequestCharacterInfoMessageHandler&& _Other) = delete;


public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	void Start();

	void DBCheck();

private:
	void ResultSend();

};