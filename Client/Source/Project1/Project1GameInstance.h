
#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "Project1GameInstance.generated.h"

UCLASS()
class PROJECT1_API UProject1GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	public:
	UProject1GameInstance();
	virtual ~UProject1GameInstance();

	private:
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
	
	EPlayerJob	m_SelectJob;

	UPROPERTY()
	class UInventoryManager* m_InventoryManager;
	
	//
	// UPROPERTY()
	// UDataTable* m_QuestInfoTable;

	public:
	UDataTable* GetSelectPlayerInfoTable() const
	{
		return m_SelectPlayerInfoTable;
	}

	EPlayerJob GetSelectJob()	const
	{
		return m_SelectJob;
	}
	void SetSelectJob(EPlayerJob Job)
	{
		m_SelectJob = Job;
	}

	class UInventoryManager* GetInventoryManager() const
	{
		return m_InventoryManager;
	}

	public:
	virtual void Init();

	public:
	const FMonsterTableInfo* FindMonsterInfo(const FString& Name);
	const FPlayerTableInfo* FindPlayerInfo(const FString& Name);
	const FSelectPlayerTableInfo* FindSelectPlayerTableInfo(const FString& Name);
	const FItemTableInfo* FindItemTableInfo(const FString& Name);
	const FBulletTableInfo* FindBulletTableInfo(const FString& Name);
	//const FQuestTableInfo* FindQuestTableInfo(const FString& Name);
};
