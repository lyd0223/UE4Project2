#pragma once
#include <memory>
#include "../Messages.h"

class CreateCharacterInfoResultMessageHandler
{
private:
	class UWorld* m_World;
	class UProject1GameInstance* m_GameInstance;
	std::shared_ptr<CreateCharacterInfoResultMessage> m_CreateCharacterInfoResultMessage;

public:
	CreateCharacterInfoResultMessageHandler(std::shared_ptr<CreateCharacterInfoResultMessage> _CreateCharacterInfoResultMessage);

	//MessageHandler는 이 아래 두 함수를 무조건 가져야함.
	void Init(UProject1GameInstance* _GameInstance, UWorld* _World);
	void Start();
	
};
