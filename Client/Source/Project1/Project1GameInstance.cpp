// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1GameInstance.h"

#include "Manager/InventoryManager.h"


UProject1GameInstance::UProject1GameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>	MonsterInfoTableAsset(TEXT("DataTable'/Game/01Resources/Monster/DTMonsterInfo.DTMonsterInfo'"));
	if (MonsterInfoTableAsset.Succeeded())
		m_MonsterInfoTable = MonsterInfoTableAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable>	PlayerInfoTableAsset(TEXT("DataTable'/Game/01Resources/Player/DTPlayerInfo.DTPlayerInfo'"));
	if (PlayerInfoTableAsset.Succeeded())
		m_PlayerInfoTable = PlayerInfoTableAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable>	SelectPlayerInfoTableAsset(TEXT("DataTable'/Game/01Resources/DataTable/DTSelectPlayerInfo.DTSelectPlayerInfo'"));
	if (SelectPlayerInfoTableAsset.Succeeded())
		m_SelectPlayerInfoTable = SelectPlayerInfoTableAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable>	ItemInfoTableAsset(TEXT("DataTable'/Game/01Resources/DataTable/DTItemTableInfo.DTItemTableInfo'"));
	if (ItemInfoTableAsset.Succeeded())
		m_ItemInfoTable = ItemInfoTableAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable>	BulletInfoTableAsset(TEXT("DataTable'/Game/01Resources/DataTable/DTBulletTableInfo.DTBulletTableInfo'"));
	if (BulletInfoTableAsset.Succeeded())
		m_BulletInfoTable = BulletInfoTableAsset.Object;

	m_SelectJob = EPlayerJob::Belica;
	
	m_InventoryManager = nullptr;
}

UProject1GameInstance::~UProject1GameInstance()
{
	
}

void UProject1GameInstance::Init()
{
	Super::Init();
	m_InventoryManager = NewObject<UInventoryManager>(this, TEXT("InventoryManager"));
	m_InventoryManager->Init();
}

const FMonsterTableInfo* UProject1GameInstance::FindMonsterInfo(const FString& Name)
{
	return m_MonsterInfoTable->FindRow<FMonsterTableInfo>(*Name, "");
}

const FPlayerTableInfo* UProject1GameInstance::FindPlayerInfo(const FString& Name)
{
	return m_PlayerInfoTable->FindRow<FPlayerTableInfo>(*Name, "");
}

const FSelectPlayerTableInfo* UProject1GameInstance::FindSelectPlayerTableInfo(const FString& Name)
{
	return m_SelectPlayerInfoTable->FindRow<FSelectPlayerTableInfo>(*Name, "");
}

const FItemTableInfo* UProject1GameInstance::FindItemTableInfo(const FString& Name)
{
	return m_ItemInfoTable->FindRow<FItemTableInfo>(*Name, "");
}
const FBulletTableInfo* UProject1GameInstance::FindBulletTableInfo(const FString& Name)
{
	return m_BulletInfoTable->FindRow<FBulletTableInfo>(*Name, "");
}
