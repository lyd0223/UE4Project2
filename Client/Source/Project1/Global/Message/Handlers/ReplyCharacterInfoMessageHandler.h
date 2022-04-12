#pragma once
#include <memory>
#include "../Messages.h"

class ReplyCharacterInfoMessageHandler
{
private:
	class UWorld* m_World;
	class UProject1GameInstance* m_GameInstance;
	std::shared_ptr<ReplyCharacterInfoMessage> m_ReplyCharacterInfoMessage;

public:
	ReplyCharacterInfoMessageHandler(std::shared_ptr<ReplyCharacterInfoMessage> _ReplyCharacterInfoMessage);

	//MessageHandler는 이 아래 두 함수를 무조건 가져야함.
	void Init(UProject1GameInstance* _GameInstance, UWorld* _World);
	void Start();
	
};
