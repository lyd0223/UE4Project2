#include "CreateCharacterInfoResultMessageHandler.h"

#include "Project1/Project1GameInstance.h"
#include "Project1/SelectCharacterGameModeBase.h"
#include "Project1/UI/SelectCharacterLevel/SelectCharacterMainWidget.h"


void CreateCharacterInfoResultMessageHandler::Start()
{
	ECreateCharacterInfoResultType ResultType = m_Message->m_CreateCharacterInfoResultType;
	switch (ResultType)
	{
	case ECreateCharacterInfoResultType::Error:
		{
			PrintViewport(2.f, FColor::Red, TEXT("CreateCharacterInfoResultMessageHandler Error!"));
			return;
		}
	case ECreateCharacterInfoResultType::OK:
		{
			ASelectCharacterGameModeBase* GameMode = Cast<ASelectCharacterGameModeBase>(m_World->GetAuthGameMode());
			if (GameMode == nullptr)
				return;
			USelectCharacterMainWidget* SelectCharacterMainWidget = Cast<USelectCharacterMainWidget>(GameMode->GetSelectHUD());
			SelectCharacterMainWidget->UIInitialize(m_Message->m_CharacterInfoList);
			break;
		}
	case ECreateCharacterInfoResultType::MAX:
		{
			PrintViewport(2.f, FColor::Red, TEXT("CreateCharacterInfoResultMessageHandler Result Type Max!"));
			return;
		}
	}
}
