#pragma once
#include <memory>
#include "../Messages.h"

class LoginResultMessageHandler
{
private:
	class UWorld* m_World;
	class UClientGameInstance* m_GameInstance;
	std::shared_ptr<LoginResultMessage> m_LoginResultMessage;

public:
	LoginResultMessageHandler(std::shared_ptr<LoginResultMessage> _LoginResultMessage);

	//MessageHandler는 이 아래 두 함수를 무조건 가져야함.
	void Init(UClientGameInstance* _GameInstance, UWorld* _World);
	void Start();
};
