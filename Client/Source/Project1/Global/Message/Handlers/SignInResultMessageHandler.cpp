#include "SignInResultMessageHandler.h"

#include "Kismet/GameplayStatics.h"
#include "Project1/GameInfo.h"


SignInResultMessageHandler::SignInResultMessageHandler(std::shared_ptr<SignInResultMessage> _SignInResultMessage)
{
	m_GameInstance = nullptr;
	m_World = nullptr;
	m_SignInResultMessage = _SignInResultMessage;
}

void SignInResultMessageHandler::Init(UProject1GameInstance* _GameInstance, UWorld* _World)
{
	m_GameInstance = _GameInstance;
	m_World = _World;
}

void SignInResultMessageHandler::Start()
{
	if(m_SignInResultMessage->m_SignInResultType == ESignInResultType::OK)
	{
		UGameplayStatics::OpenLevel(m_World, TEXT("SelectCharacter"));
		
	}
	else
	{
		PrintViewport(2.f, FColor::Red, TEXT("Login Failed"));
	}
}


