#pragma once
#include <memory>
#include "../Messages.h"

class ChatMessageHandler
{
private:
	class UWorld* m_World;
	class UClientGameInstance* m_GameInstance;
	std::shared_ptr<ChatMessage> m_ChatMessage;

public:
	ChatMessageHandler(std::shared_ptr<ChatMessage> _ChatMessage);

	//MessageHandler는 이 아래 두 함수를 무조건 가져야함.
	void Init(UClientGameInstance* _GameInstance, UWorld* _World);
	void Start();
};
