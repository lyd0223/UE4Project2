#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

/*
Usage		:  MessageHandler
Category	:
Description :  CreateCharacterInfo 패킷이 오면 처리해야할 동작을 구현.
*/

class CreateCharacterInfoMessageHandler final
	: public std::enable_shared_from_this<CreateCharacterInfoMessageHandler>
{
private:
	//패킷을 보낸 세션
	std::shared_ptr<TCPSession> m_TCPSession;

	//온 패킷
	std::shared_ptr<CreateCharacterInfoMessage> m_CreateCharacterInfoMessage;

	CreateCharacterInfoResultMessage m_CreateCharacterInfoResultMessage;

public: //Default
	CreateCharacterInfoMessageHandler(std::shared_ptr<TCPSession> _TCPSession,
		std::shared_ptr<CreateCharacterInfoMessage> _CreateCharacterInfoMessage);
	~CreateCharacterInfoMessageHandler();

	CreateCharacterInfoMessageHandler(const CreateCharacterInfoMessageHandler& _Other) = delete;
	CreateCharacterInfoMessageHandler(CreateCharacterInfoMessageHandler&& _Other)		noexcept = delete;
	CreateCharacterInfoMessageHandler& operator=(const CreateCharacterInfoMessageHandler& _Other) = delete;
	CreateCharacterInfoMessageHandler& operator=(CreateCharacterInfoMessageHandler&& _Other) = delete;


public:
	//메시지 받았을때 실행하는 함수.
	void Start();

	void DBCheck();

private:
	void ResultSend();

};
