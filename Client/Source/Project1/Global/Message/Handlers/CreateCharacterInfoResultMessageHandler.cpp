#include "CreateCharacterInfoResultMessageHandler.h"

CreateCharacterInfoResultMessageHandler::CreateCharacterInfoResultMessageHandler(std::shared_ptr<CreateCharacterInfoResultMessage> _CreateCharacterInfoResultMessage)
{
	m_GameInstance = nullptr;
	m_World = nullptr;
	m_CreateCharacterInfoResultMessage = _CreateCharacterInfoResultMessage;
}

void CreateCharacterInfoResultMessageHandler::Init(UProject1GameInstance* _GameInstance, UWorld* _World)
{
	m_GameInstance = _GameInstance;
	m_World = _World;
}

void CreateCharacterInfoResultMessageHandler::Start()
{
	// for(auto& CharacterInfo : m_CreateCharacterInfoResultMessage->m_CharacterInfoList)
	// {
	// 	ASelectCharacterGameModeBase* GameMode = Cast<ASelectCharacterGameModeBase>(m_World->GetAuthGameMode());
	// 	if(GameMode == nullptr)
	// 		return;
	// 	USelectCharacterMainWidget* SelectCharacterMainWidget = Cast<USelectCharacterMainWidget>(GameMode->GetSelectHUD());
	// 	SelectCharacterMainWidget->UIInitialize(m_ReplyCharacterInfoMessage->m_CharacterInfoList);
	// }
	
}
