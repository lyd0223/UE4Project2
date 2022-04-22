#include "SignInResultMessageHandler.h"

#include "Kismet/GameplayStatics.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/StartGameModeBase.h"
#include "Project1/UI/StartLevel/StartMainWidget.h"


void SignInResultMessageHandler::Start()
{
	if(m_Message->m_SignInResultType == ESignInResultType::OK)
	{
		m_GameInstance->SetUserIdx(m_Message->m_UserIdx);
		UGameplayStatics::OpenLevel(m_World, TEXT("SelectCharacter"));
	}
	else
	{
		//PrintViewport(2.f, FColor::Red, TEXT("Login Failed"));
		AStartGameModeBase* GameMode = Cast<AStartGameModeBase>(m_World->GetAuthGameMode());
		GameMode->GetStartMainWidget()->PopUpMessage(TEXT("SignIn Failed"));
	}
}


