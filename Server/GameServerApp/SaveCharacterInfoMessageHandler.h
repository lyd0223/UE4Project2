#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>


class SaveCharacterInfoMessageHandler final
	: public std::enable_shared_from_this<SaveCharacterInfoMessageHandler>
{
private:
	//패킷을 보낸 세션
	std::shared_ptr<TCPSession> m_TCPSession;

	//온 패킷
	std::shared_ptr<SaveCharacterInfoMessage> m_SaveCharacterInfoMessage;


public: //Default
	SaveCharacterInfoMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<SaveCharacterInfoMessage> _SaveCharacterInfoMessage);
	~SaveCharacterInfoMessageHandler();

	SaveCharacterInfoMessageHandler(const SaveCharacterInfoMessageHandler& _Other) = delete;
	SaveCharacterInfoMessageHandler(SaveCharacterInfoMessageHandler&& _Other)		noexcept = delete;
	SaveCharacterInfoMessageHandler& operator=(const SaveCharacterInfoMessageHandler& _Other) = delete;
	SaveCharacterInfoMessageHandler& operator=(SaveCharacterInfoMessageHandler&& _Other) = delete;


public:
	//메시지 받았을때 실행하는 함수.
	void Start();

private:
	void DBCheck();
	//void ResultSend();

};

