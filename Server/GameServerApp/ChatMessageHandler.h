#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

/*
Usage		:
Category	:
Description :  채팅 패킷이 오면 처리해야할 동작을 구현.
*/

class ChatMessageHandler final
	: public std::enable_shared_from_this<ChatMessageHandler>
{
private:
	//패킷을 보낸 세션
	std::shared_ptr<TCPSession> m_TCPSession;

	//온 패킷
	std::shared_ptr<ChatMessage> m_ChatMessage;

	//결과 패킷
	LoginResultMessage m_LoginResultMessage;

public: //Default
	ChatMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<ChatMessage> _ChatMessage);
	~ChatMessageHandler();

	ChatMessageHandler(const ChatMessageHandler& _Other) = delete;
	ChatMessageHandler(ChatMessageHandler&& _Other)		noexcept = delete;

protected:
	ChatMessageHandler& operator=(const ChatMessageHandler& _Other) = delete;
	ChatMessageHandler& operator=(ChatMessageHandler&& _Other) = delete;


public:
	//메시지 받았을때 실행하는 함수.
	void Start();

private:
	void ResultSend();

};