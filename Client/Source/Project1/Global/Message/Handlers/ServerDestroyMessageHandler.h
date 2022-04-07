#pragma once
#include <memory>
#include "../Messages.h"

class ServerDestroyMessageHandler
{
private:
	class UWorld* m_World;
	class UProject1GameInstance* m_GameInstance;
	std::shared_ptr<ServerDestroyMessage> m_ServerDestroyMessage;

public:
	ServerDestroyMessageHandler(std::shared_ptr<ServerDestroyMessage> _ServerDestroyMessage);

	//MessageHandler는 이 아래 두 함수를 무조건 가져야함.
	void Init(UProject1GameInstance* _GameInstance, UWorld* _World);
	void Start();
};
