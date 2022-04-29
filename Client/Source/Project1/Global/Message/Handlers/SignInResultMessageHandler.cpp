#include "SignInResultMessageHandler.h"

#include "Kismet/GameplayStatics.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/StartGameModeBase.h"
#include "Project1/UI/StartLevel/StartMainWidget.h"


void SignInResultMessageHandler::Start()
{
	ESignInResultType Result = m_Message->m_SignInResultType;
	switch (Result)
	{
	case ESignInResultType::OK:
		{
			m_GameInstance->SetUserIdx(m_Message->m_UserIdx);
			UGameplayStatics::OpenLevel(m_World, TEXT("SelectCharacter"));
			break;
		}
	case ESignInResultType::Failed_NoUser:
		{
			AStartGameModeBase* GameMode = Cast<AStartGameModeBase>(m_World->GetAuthGameMode());
			GameMode->GetStartMainWidget()->PopUpMessage(TEXT("No ID!"));
			break;
		}
	case ESignInResultType::Failed_WrongPassword:
		{
			AStartGameModeBase* GameMode = Cast<AStartGameModeBase>(m_World->GetAuthGameMode());
			GameMode->GetStartMainWidget()->PopUpMessage(TEXT("Wrong Password!"));
			break;
		}

	case ESignInResultType::Error:

		break;
	case ESignInResultType::MAX:

		break;
	}
}
