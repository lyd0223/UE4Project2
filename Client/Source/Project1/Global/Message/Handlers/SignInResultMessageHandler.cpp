#include "SignInResultMessageHandler.h"
#include "../../ClientGameInstance.h"
#include "UnrealClient/Login/LoginHUD.h"
#include "UnrealClient/Login/LoginUI.h"

SignInResultMessageHandler::SignInResultMessageHandler(
	std::shared_ptr<SignInResultMessage> _SignInResultMessage)
{
	m_SignInResultMessage = _SignInResultMessage;
}

void SignInResultMessageHandler::Init(UClientGameInstance* _GameInstance, UWorld* _World)
{
	m_GameInstance = _GameInstance;
	m_World = _World;
}

void SignInResultMessageHandler::Start()
{
	ESignInResultType SignInResultType = m_SignInResultMessage->m_SignInResultType;
	switch (SignInResultType)
	{
	case ESignInResultType::OK:
		//회원가입 완료
		{
			ALoginHUD* LoginHUD = Cast<ALoginHUD>(m_World->GetFirstPlayerController()->GetHUD());
			LoginHUD->GetLoginUI()->SignInUIOff();
			LoginHUD->GetLoginUI()->SignInSucceedPopUpOn();
			break;
		}
	case ESignInResultType::Error_DuplicateID:
		{
			break;
		}
	case ESignInResultType::Error_NonAvailableID:
		//유효하지않은 ID
		{
			ALoginHUD* LoginHUD = Cast<ALoginHUD>(m_World->GetFirstPlayerController()->GetHUD());
			LoginHUD->GetLoginUI()->SignInFailedPopUpOn();
			break;
		}
	case ESignInResultType::MAX:
		//이런경우 아예 리턴때려버려야함.
		{
			break;
		}
	}

}
