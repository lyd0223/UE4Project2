#include "ServerDestroyMessageHandler.h"

#include "Kismet/GameplayStatics.h"

void ServerDestroyMessageHandler::Start()
{
	if(m_World->GetName() != TEXT("LoginLevel"))
	{
		UGameplayStatics::OpenLevel(m_World, TEXT("LoginLevel"));
	}
}


