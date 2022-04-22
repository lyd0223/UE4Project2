#include "CreateCharacterInfoResultMessageHandler.h"

#include "Project1/Project1GameInstance.h"


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
			m_GameInstance->SetPlayingCharacterInfo(m_Message->m_CharacterInfo);

			FString Str = TEXT("");
			UClientBlueprintFunctionLibrary::UTF8ToFString(m_Message->m_CharacterInfo.m_ClassName,
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
