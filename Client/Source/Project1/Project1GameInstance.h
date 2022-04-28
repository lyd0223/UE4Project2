#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include <memory>
#include <vector>

#include "Global/Message/ContentsStruct.h"
#include "Project1GameInstance.generated.h"


class GameServerMessage;

class ClientRecvThread : public FRunnable
{
private:
	FSocket* m_RecvSocket;
	TAtomic<bool> m_IsAppClosed;

	TQueue<std::shared_ptr<GameServerMessage>, EQueueMode::Spsc>* m_MessageQueue;

public:
	ClientRecvThread(FSocket* _RecvSocket, TQueue<std::shared_ptr<GameServerMessage>>* _MessageQueue);

	virtual uint32 Run() override;

	void Close();
};

UCLASS()
class PROJECT1_API UProject1GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UProject1GameInstance();
	virtual ~UProject1GameInstance() override;

private:
	//-------------------------------------------------------
	//서버용 멤버변수
	TQueue<std::shared_ptr<GameServerMessage>> m_MessageQueue;
	ClientRecvThread* m_RecvThread;
	FRunnableThread* m_ThreadRunalbe;

	ISocketSubsystem* m_SocketSubSystem;
	FSocket* m_Socket;

	bool m_IsServerConnected;
	//셀프 패킷 실험용으로 클라이언트 모드를 만들어놓음.
	bool m_IsClientMode;

	unsigned int m_UserIdx;
	FCharacterInfo m_PlayingCharacterInfo;
	// ---------------------------------------------------------
	
	UPROPERTY()
	UDataTable* m_MonsterInfoTable;

	UPROPERTY()
	UDataTable* m_PlayerInfoTable;

	UPROPERTY()
	UDataTable* m_SelectPlayerInfoTable;

	UPROPERTY()
	UDataTable* m_ItemInfoTable;

	UPROPERTY()
	UDataTable* m_BulletInfoTable;

	EPlayerJob m_SelectJob;

	UPROPERTY()
	class UInventoryManager* m_InventoryManager;

	TMap<int, class AOtherPlayerCharacter*> m_PlayingOtherPlayerMap;
	TMap<FString, TSubclassOf<class AOtherPlayerCharacter>> m_OtherPlayerCharacterClassMap;
public:
	//Getter & Setter
	//------------------------서버용-----------------------
	bool GetIsClientMode() const
	{
		return m_IsClientMode;
	}
	void SetIsClientMode(bool _IsClientMode)
	{
		m_IsClientMode = _IsClientMode;
	}

	bool IsEmptyMessage() const
	{
		return m_MessageQueue.IsEmpty();
	}

	unsigned int GetUserIdx() const
	{
		return m_UserIdx;
	}
	void SetUserIdx(int _UserIdx)
	{
		m_UserIdx = _UserIdx;
	}
	
	FCharacterInfo GetPlayingCharacterInfo() const
	{
		return m_PlayingCharacterInfo;
	}
	void SetPlayingCharacterInfo(FCharacterInfo _CharacterInfo)
	{
		m_PlayingCharacterInfo = _CharacterInfo;
	}
	void SetPlayingCharacterInfo(const FPlayerInfo& PlayerInfo);

	
	void AddPlayingOtherCharacter(int _UserIdx, class AOtherPlayerCharacter* _Character)
	{
		m_PlayingOtherPlayerMap.Add(_UserIdx, _Character);
	}
	void RemovePlayingOtherCharacter(int _UserIdx)
	{
		m_PlayingOtherPlayerMap.Remove(_UserIdx);
	}
	void RemoveAllPlayingOtherCharacter()
	{
		m_PlayingOtherPlayerMap.Reset();
	}
	class AOtherPlayerCharacter* GetPlayingOtherCharacter(int _UserIdx) const
	{
		if(m_PlayingOtherPlayerMap.Find(_UserIdx) == nullptr)
			return nullptr;
		return m_PlayingOtherPlayerMap[_UserIdx];
	}

	//임시 -----------
	TMap<int, class AOtherPlayerCharacter*> GetMap()
	{
		return m_PlayingOtherPlayerMap;
	}

	TSubclassOf<AOtherPlayerCharacter> GetOtherPlayerCharacterClass(std::string _Class) const
	{
		FString Class = TEXT("");
		UClientBlueprintFunctionLibrary::UTF8ToFString(_Class, Class);
		if(m_OtherPlayerCharacterClassMap.Find(Class) == nullptr)
			return nullptr;
		return m_OtherPlayerCharacterClassMap[Class];
	}
	
	// ---------------------------------------------------
	
	UDataTable* GetSelectPlayerInfoTable() const
	{
		return m_SelectPlayerInfoTable;
	}

	EPlayerJob GetSelectJob() const
	{
		return m_SelectJob;
	}

	void SetSelectJob(EPlayerJob Job)
	{
		m_SelectJob = Job;
	}
	void SetSelectJob(const FString& JobStr)
	{
		if(JobStr == TEXT("Belica"))
			m_SelectJob = EPlayerJob::Belica;
		else if(JobStr == TEXT("Revenant"))
			m_SelectJob = EPlayerJob::Revenant;
		else if(JobStr == TEXT("Wraith"))
			m_SelectJob = EPlayerJob::Wraith;
		else if(JobStr == TEXT("TwinBlaster"))
			m_SelectJob = EPlayerJob::TwinBlaster;
	}
	class UInventoryManager* GetInventoryManager() const
	{
		return m_InventoryManager;
	}

public:
	virtual void Init() override;

	// ----------------------------- 서버용 ----------------------------------
	bool ServerConnect(const FString& _IPString, const FString& _PortString);
	
	void PushClientMessage(std::shared_ptr<GameServerMessage> _Message);
	
	std::shared_ptr<GameServerMessage> PopMessage();
	
	bool Send(const std::vector<uint8>& _Data);
	
	void Close();
	
	virtual void FinishDestroy() override;
	
	bool ThreadAvailableCheck();

	void InventorySetting();

	// -----------------------------------------------------------------------
	
	const FMonsterTableInfo* FindMonsterInfo(const FString& Name);
	const FPlayerTableInfo* FindPlayerInfo(const FString& Name);
	const FSelectPlayerTableInfo* FindSelectPlayerTableInfo(const FString& Name);
	const FItemTableInfo* FindItemTableInfo(const FString& Name);
	const FItemTableInfo* FindItemTableInfo(int Index);
	const FBulletTableInfo* FindBulletTableInfo(const FString& Name);
	//const FQuestTableInfo* FindQuestTableInfo(const FString& Name);
};
