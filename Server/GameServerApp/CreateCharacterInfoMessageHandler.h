#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

/*
Usage		:  MessageHandler
Category	:
Description :  CreateCharacterInfo ��Ŷ�� ���� ó���ؾ��� ������ ����.
*/

class CreateCharacterInfoMessageHandler final
	: public std::enable_shared_from_this<CreateCharacterInfoMessageHandler>
{
private:
	//��Ŷ�� ���� ����
	std::shared_ptr<TCPSession> m_TCPSession;

	//�� ��Ŷ
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
	//�޽��� �޾����� �����ϴ� �Լ�.
	void Start();

	void DBCheck();

private:
	void ResultSend();

};
