#include "ReplyCharacterInfoMessageHandler.h"

#include "Project1/SelectCharacterGameModeBase.h"
#include "Project1/UI/SelectCharacterLevel/SelectCharacterMainWidget.h"

ReplyCharacterInfoMessageHandler::ReplyCharacterInfoMessageHandler(
	std::shared_ptr<ReplyCharacterInfoMessage> _ReplyCharacterInfoMessage)
{
	m_GameInstance = nullptr;
	m_World = nullptr;
	m_ReplyCharacterInfoMessage = _ReplyCharacterInfoMessage;
}

void ReplyCharacterInfoMessageHandler::Init(UProject1GameInstance* _GameInstance, UWorld* _World)
{
	m_GameInstance = _GameInstance;
	m_World = _World;
}

void ReplyCharacterInfoMessageHandler::Start()
{
	ASelectCharacterGameModeBase* GameMode = Cast<ASelectCharacterGameModeBase>(m_World->GetAuthGameMode());
	if (GameMode == nullptr)
		return;
	USelectCharacterMainWidget* SelectCharacterMainWidget = Cast<USelectCharacterMainWidget>(GameMode->GetSelectHUD());
	SelectCharacterMainWidget->UIInitialize(m_ReplyCharacterInfoMessage->m_CharacterInfoList);
}
