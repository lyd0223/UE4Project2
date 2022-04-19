#include "CreateCharacterInfoResultMessageHandler.h"

#include "Project1/Project1GameInstance.h"


CreateCharacterInfoResultMessageHandler::CreateCharacterInfoResultMessageHandler(
	std::shared_ptr<CreateCharacterInfoResultMessage> _CreateCharacterInfoResultMessage)
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
	ECreateCharacterInfoResultType ResultType = m_CreateCharacterInfoResultMessage->m_CreateCharacterInfoResultType;
	switch (ResultType)
	{
	case ECreateCharacterInfoResultType::Error:
		{
			PrintViewport(2.f, FColor::Red, TEXT("CreateCharacterInfoResultMessageHandler Error!"));
			return;
		}
	case ECreateCharacterInfoResultType::OK:
		{
			m_GameInstance->SetPlayingCharacterInfo(m_CreateCharacterInfoResultMessage->m_CharacterInfo);

			FString Str = TEXT("");
			UClientBlueprintFunctionLibrary::UTF8ToFString(m_CreateCharacterInfoResultMessage->m_CharacterInfo.m_ClassName,
														Str);

			m_GameInstance->SetSelectJob(Str);
			UGameplayStatics::OpenLevel(m_World, TEXT("WaitingRoom"));
			break;
		}
	case ECreateCharacterInfoResultType::MAX:
		{
			PrintViewport(2.f, FColor::Red, TEXT("CreateCharacterInfoResultMessageHandler Result Type Max!"));
			return;
		}
	}
}
