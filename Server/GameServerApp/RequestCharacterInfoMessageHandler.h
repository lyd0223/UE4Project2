#pragma once

#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

/*
Usage		:  MessageHandler
Category	:
Description :  RequestCharacterInfo 패킷이 오면 처리해야할 동작을 구현.
*/

class RequestCharacterInfoMessageHandler final
	: public std::enable_shared_from_this<RequestCharacterInfoMessageHandler>
{
private:
	//패킷을 보낸 세션
	std::shared_ptr<TCPSession> m_TCPSession;

	//온 패킷
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
	//메시지 받았을때 실행하는 함수.
	void Start();

	void DBCheck();

private:
	void ResultSend();

};