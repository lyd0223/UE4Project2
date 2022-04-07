#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

/*
Usage		:
Category	:
Description :  ä�� ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class ChatMessageHandler final
	: public std::enable_shared_from_this<ChatMessageHandler>
{
private:
	//��Ŷ�� ���� ����
	std::shared_ptr<TCPSession> m_TCPSession;

	//�� ��Ŷ
	std::shared_ptr<ChatMessage> m_ChatMessage;


public: //Default
	ChatMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<ChatMessage> _ChatMessage);
	~ChatMessageHandler();

	ChatMessageHandler(const ChatMessageHandler& _Other) = delete;
	ChatMessageHandler(ChatMessageHandler&& _Other)		noexcept = delete;

protected:
	ChatMessageHandler& operator=(const ChatMessageHandler& _Other) = delete;
	ChatMessageHandler& operator=(ChatMessageHandler&& _Other) = delete;


public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	void Start();

private:
	void ResultSend();

};