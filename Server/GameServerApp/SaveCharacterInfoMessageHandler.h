#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>


class SaveCharacterInfoMessageHandler final
	: public std::enable_shared_from_this<SaveCharacterInfoMessageHandler>
{
private:
	//��Ŷ�� ���� ����
	std::shared_ptr<TCPSession> m_TCPSession;

	//�� ��Ŷ
	std::shared_ptr<SaveCharacterInfoMessage> m_SaveCharacterInfoMessage;


public: //Default
	SaveCharacterInfoMessageHandler(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<SaveCharacterInfoMessage> _SaveCharacterInfoMessage);
	~SaveCharacterInfoMessageHandler();

	SaveCharacterInfoMessageHandler(const SaveCharacterInfoMessageHandler& _Other) = delete;
	SaveCharacterInfoMessageHandler(SaveCharacterInfoMessageHandler&& _Other)		noexcept = delete;
	SaveCharacterInfoMessageHandler& operator=(const SaveCharacterInfoMessageHandler& _Other) = delete;
	SaveCharacterInfoMessageHandler& operator=(SaveCharacterInfoMessageHandler&& _Other) = delete;


public:
	//�޽��� �޾����� �����ϴ� �Լ�.
	void Start();

private:
	void DBCheck();
	//void ResultSend();

};

