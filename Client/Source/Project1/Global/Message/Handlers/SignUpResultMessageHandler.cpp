#include "SignUpResultMessageHandler.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/StartGameModeBase.h"
#include "Project1/UI/StartLevel/StartMainWidget.h"

void SignUpResultMessageHandler::Start()
{
	ESignUpResultType SignUpResultType = m_Message->m_SignUpResultType;
	switch (SignUpResultType)
	{
	case ESignUpResultType::OK:
		//회원가입 완료
		{
			//PrintViewport(2.f, FColor::Green, TEXT("SignUp Success"));
			AStartGameModeBase* GameMode = Cast<AStartGameModeBase>(m_World->GetAuthGameMode());
			GameMode->GetStartMainWidget()->PopUpMessage(TEXT("SignUp Succeed"));
			break;
		}
	case ESignUpResultType::Error_DuplicateID:
		{
			break;
		}
	case ESignUpResultType::Error_NonAvailableID:
		//유효하지않은 ID
		{
			//PrintViewport(2.f, FColor::Red, TEXT("SignUp Failed"));
			AStartGameModeBase* GameMode = Cast<AStartGameModeBase>(m_World->GetAuthGameMode());
			GameMode->GetStartMainWidget()->PopUpMessage(TEXT("SignUp Failed"));
			
			break;
		}
	case ESignUpResultType::MAX:
		//이런경우 아예 리턴때려버려야함.
		{
			break;
		}
	}

}
