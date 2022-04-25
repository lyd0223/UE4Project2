#include "CharacterMoveMessageHandler.h"
#include "Project1/WaitingRoomGameModeBase.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Player/WaitingRoomLevel/OtherPlayerCharacter.h"

void CharacterMoveMessageHandler::Start()
{
	if (m_GameInstance == nullptr)
		return;
	//서버에서 패킷을 브로드캐스팅했을때 나 자신또한 포함했기때문에,
	//나 자신이라면 무시한다.
	if (m_Message->m_CharacterInfo.m_UserIdx == m_GameInstance->GetUserIdx())
		return;
	AWaitingRoomGameModeBase* GameMode = Cast<AWaitingRoomGameModeBase>(m_World->GetAuthGameMode());
	if (GameMode == nullptr)
		return;
	//UserIdx확인 후 움직여준다.
	if (m_GameInstance->GetPlayingOtherCharacter(m_Message->m_CharacterInfo.m_UserIdx) == nullptr)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AOtherPlayerCharacter* OtherPlayerCharacter = m_World->SpawnActor<AOtherPlayerCharacter>(
			m_GameInstance->GetOtherPlayerCharacterClass(m_Message->m_CharacterInfo.m_ClassName),
			m_Message->m_Pos,
			FRotator(m_Message->m_Rot.X, m_Message->m_Rot.Y, m_Message->m_Rot.Z),
			param);
		m_GameInstance->AddPlayingOtherCharacter(m_Message->m_CharacterInfo.m_UserIdx, OtherPlayerCharacter);
		return;
	}
	AOtherPlayerCharacter* OtherPlayerCharacter = m_GameInstance->GetPlayingOtherCharacter(m_Message->m_CharacterInfo.m_UserIdx);
	OtherPlayerCharacter->Move(m_Message->m_Pos, FRotator(m_Message->m_Rot.X, m_Message->m_Rot.Y, m_Message->m_Rot.Z));
}
