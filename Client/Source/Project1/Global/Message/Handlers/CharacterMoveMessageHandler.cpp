#include "CharacterMoveMessageHandler.h"
#include "Project1/WaitingRoomGameModeBase.h"
#include "Project1/Project1GameInstance.h"

void CharacterMoveMessageHandler::Start()
{
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(m_World->GetGameInstance());
	if(GameInstance == nullptr)
		return;
	//서버에서 패킷을 브로드캐스팅했을때 나 자신또한 포함했기때문에,
	//나 자신이라면 무시한다.
	if(m_Message->m_UserIdx == GameInstance->GetUserIdx())
		return;

	//UserIdx확인 후 움직여준다.
	
	
}
