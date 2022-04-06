#pragma once
#include <memory>
#include "../Messages.h"

class SignInResultMessageHandler
{
private:
	class UWorld* m_World;
	class UClientGameInstance* m_GameInstance;
	std::shared_ptr<SignInResultMessage> m_SignInResultMessage;

public:
	SignInResultMessageHandler(std::shared_ptr<SignInResultMessage> _SignInResultMessage);

	//MessageHandler는 이 아래 두 함수를 무조건 가져야함.
	void Init(UClientGameInstance* _GameInstance, UWorld* _World);
	void Start();
	
};
