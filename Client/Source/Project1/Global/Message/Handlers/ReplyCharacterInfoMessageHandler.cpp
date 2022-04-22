#include "ReplyCharacterInfoMessageHandler.h"

#include "Project1/SelectCharacterGameModeBase.h"
#include "Project1/UI/SelectCharacterLevel/SelectCharacterMainWidget.h"

void ReplyCharacterInfoMessageHandler::Start()
{
	ASelectCharacterGameModeBase* GameMode = Cast<ASelectCharacterGameModeBase>(m_World->GetAuthGameMode());
	if (GameMode == nullptr)
		return;
	USelectCharacterMainWidget* SelectCharacterMainWidget = Cast<USelectCharacterMainWidget>(GameMode->GetSelectHUD());
	SelectCharacterMainWidget->UIInitialize(m_Message->m_CharacterInfoList);
}
