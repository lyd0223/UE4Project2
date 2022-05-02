// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"

#include "Project1/Project1GameInstance.h"
#include "Project1/Project1GameModeBase.h"
#include "Project1/WaitingRoomGameModeBase.h"
#include "Project1/Effect/NormalEffect.h"
#include "Project1/Player/PlayerCharacter.h"
#include "Project1/UI/MainHUDWidget.h"
#include "Project1/UI/WaitingRoomLevel/WaitingRoomMainWidget.h"
#include "Project1/UI/WaitingRoomLevel/Store/StoreMainWidget.h"
#include "Project1/UI/QuickItemSlotWidget.h"


UInventoryManager::UInventoryManager()
{
	m_MaxWeight = 36;
	m_NowWeight = 0;
	m_Gold = 0;
	m_OwnerCharacter = nullptr;
}

void UInventoryManager::Init()
{
}


void UInventoryManager::AddGold(uint64 _Gold)
{
	m_Gold += _Gold;
}

void UInventoryManager::DeductGold(uint64 _Gold)
{
	m_Gold -= _Gold;
}

void UInventoryManager::AddItem(FItem* Item)
{
	if (Item->ItemTableInfo->ItemType == EItemType::Gold)
	{
		AddGold(Item->Count);
		SetUI(Item);
	}
	//아이템이 이미 인벤토리에 있는지 판단한다.
	bool IsAlreadyHave = false;
	for (auto MyItem : m_ItemArray)
	{
		//이미 있다면 카운트만 추가.
		if (MyItem->ItemTableInfo == Item->ItemTableInfo)
		{
			MyItem->Count += Item->Count;
			IsAlreadyHave = true;

			//delete Item;
			Item = MyItem;

			break;
		}
	}
	//인벤토리에 이미 잇지않다면 ItemArray에 추가.
	if (!IsAlreadyHave)
		m_ItemArray.Add(Item);

	SetUI(Item);
	//게임모드에맞는 UI 수정.
	/*
	 WaitingRoom	-> 
	 Main			->
	 */
	//m_UIDelegate.Execute(ItemTableInfo);
}

void UInventoryManager::DeductItem(FItem* Item)
{
	for (auto MyItem : m_ItemArray)
	{
		if (MyItem == Item)
		{
			Item->Count--;

			if (Item->Count == 0)
			{
				m_ItemArray.Remove(Item);

				//delete Item;
			}

			//사용 아이템일 시 처리
			if (Item->ItemTableInfo->ItemType == EItemType::Uses_Buff
				|| Item->ItemTableInfo->ItemType == EItemType::Uses_Potion)
			{
				if (Item->ItemTableInfo->ItemType == EItemType::Uses_Potion)
				{
					for (auto ItemOption : Item->ItemTableInfo->ItemOptionArray)
					{
						if (m_OwnerCharacter)
						{
							APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(m_OwnerCharacter);
							FPlayerInfo& PlayerInfo = PlayerCharacter->GetPlayerInfo();
							switch (ItemOption.OptionType)
							{
							case EItemOptionType::HPRecovery:
								PlayerInfo.HP += ItemOption.OptionAmount;
								if (PlayerInfo.HP > PlayerInfo.HPMax)
									PlayerInfo.HP = PlayerInfo.HPMax;
								break;
							case EItemOptionType::SPRecovery:
								PlayerInfo.HP += ItemOption.OptionAmount;
								if (PlayerInfo.SP > PlayerInfo.SPMax)
									PlayerInfo.SP = PlayerInfo.SPMax;
								break;
							}
							PlayerCharacter->SetUI();
						}
					}
				}
				else if (Item->ItemTableInfo->ItemType == EItemType::Uses_Buff)
				{
					if (m_OwnerCharacter)
					{
						AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(
							m_OwnerCharacter->GetWorld()->GetAuthGameMode());
						UBuffMainWidget* BuffMainWidget = Cast<UBuffMainWidget>(
							GameModeBase->GetMainHUDWidget()->GetBuffMainWidget());
						BuffMainWidget->SetPlayerCharacter(Cast<APlayerCharacter>(m_OwnerCharacter));
						BuffMainWidget->AddBuff(Item->ItemTableInfo, 10.f);
					}
				}
				FActorSpawnParameters param;
				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				ANormalEffect* Effect = m_OwnerCharacter->GetWorld()->SpawnActor<ANormalEffect>(
					ANormalEffect::StaticClass(), m_OwnerCharacter->GetActorLocation(),
					FRotator::ZeroRotator, param);
				Effect->LoadSoundAsync(TEXT("PotionDrink"));
				Effect->SetSoundVolume(0.5f);
				Effect->SetLifeTime(1.f);
			}
		}
	}
}

void UInventoryManager::SetUI(FItem* Item)
{
	if (m_OwnerCharacter == nullptr)
		return;
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(m_OwnerCharacter);
	if (PlayerCharacter == nullptr)
		return;
	UWorld* World = PlayerCharacter->GetWorld();
	if (World == nullptr)
		return;
	//WaitingRoom Level
	if (PlayerCharacter->GetIsWaitingRoom() == true)
	{
		AWaitingRoomGameModeBase* GameMode = Cast<AWaitingRoomGameModeBase>(World->GetAuthGameMode());
		if (GameMode == nullptr)
			return;
		if (Item->ItemTableInfo->ItemType == EItemType::Gold)
		{
			GameMode->GetMainWidget()->GetMenuWidget()->GetInventoryWidget()->SetGoldText(m_Gold);
			GameMode->GetMainWidget()->GetStoreMainWidget()->GetInventoryWidget()->SetGoldText(m_Gold);
			return;
		}
		GameMode->GetMainWidget()->GetMenuWidget()->GetInventoryWidget()->AddItem(Item);
		GameMode->GetMainWidget()->GetStoreMainWidget()->GetInventoryWidget()->AddItem(Item);
		
		m_NowWeight = m_ItemArray.Num();
		GameMode->GetMainWidget()->GetMenuWidget()->GetInventoryWidget()->SetWeightText(m_NowWeight,m_MaxWeight);
		GameMode->GetMainWidget()->GetStoreMainWidget()->GetInventoryWidget()->SetWeightText(m_NowWeight,m_MaxWeight);
		
	}
		//Main Level
	else
	{
		AProject1GameModeBase* GameMode = Cast<AProject1GameModeBase>(World->GetAuthGameMode());
		if (GameMode == nullptr)
			return;
		if (Item->ItemTableInfo->ItemType == EItemType::Gold)
		{
			GameMode->GetMainHUDWidget()->GetMenuWidget()->GetInventoryWidget()->SetGoldText(m_Gold);
			return;
		}
		GameMode->GetMainHUDWidget()->GetMenuWidget()->GetInventoryWidget()->AddItem(Item);
		GameMode->GetMainHUDWidget()->GetQuickSlotWidget()->RefreshItems(Item);
		
		m_NowWeight = m_ItemArray.Num();
		GameMode->GetMainHUDWidget()->GetMenuWidget()->GetInventoryWidget()->SetWeightText(m_NowWeight,m_MaxWeight);
	}
}

void UInventoryManager::SetUI(uint64 _Gold)
{
	if (m_OwnerCharacter == nullptr)
		return;
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(m_OwnerCharacter);
	if (PlayerCharacter == nullptr)
		return;
	UWorld* World = PlayerCharacter->GetWorld();
	if (World == nullptr)
		return;
	//WaitingRoom Level
	if (PlayerCharacter->GetIsWaitingRoom() == true)
	{
		AWaitingRoomGameModeBase* GameMode = Cast<AWaitingRoomGameModeBase>(World->GetAuthGameMode());
		if (GameMode == nullptr)
			return;
		GameMode->GetMainWidget()->GetMenuWidget()->GetInventoryWidget()->SetGoldText(m_Gold);
		GameMode->GetMainWidget()->GetStoreMainWidget()->GetInventoryWidget()->SetGoldText(m_Gold);
	}
	//Main Level
	else
	{
		AProject1GameModeBase* GameMode = Cast<AProject1GameModeBase>(World->GetAuthGameMode());
		if (GameMode == nullptr)
			return;
		GameMode->GetMainHUDWidget()->GetMenuWidget()->GetInventoryWidget()->SetGoldText(m_Gold);
	}
}

void UInventoryManager::SaveCharacterInfoInventoryData(FCharacterInfo& CharacterInfo)
{
	CharacterInfo.m_InventoryData.clear();
	CharacterInfo.m_InventoryData.resize(800);

	//InventoryData는 vector<char>형태인데, 여기에 ItemIdx(int)/ItemCount(int)를 밀어넣는다.
	int pivot = 0;
	memcpy(&CharacterInfo.m_InventoryData[pivot], &m_Gold, sizeof(uint64));
	pivot += sizeof(uint64);
	for (auto Item : m_ItemArray)
	{
		memcpy(&CharacterInfo.m_InventoryData[pivot], &Item->ItemTableInfo->Idx, sizeof(int));
		pivot += sizeof(int);
		memcpy(&CharacterInfo.m_InventoryData[pivot], &Item->Count, sizeof(int));
		pivot += sizeof(int);
	}
}

void UInventoryManager::LoadCharacterInfoInventoryData(const FCharacterInfo& CharacterInfo)
{
	m_ItemArray.Reset();
	std::vector<unsigned char> InventoryData = CharacterInfo.m_InventoryData;

	//인벤토리가 비어있는경우.
	if (InventoryData.size() < sizeof(int))
		return;

	m_Gold = *(uint64*)&InventoryData[0];
	SetUI(m_Gold);

	for (int i = sizeof(uint64); i < InventoryData.size();)
	{
		if (m_OwnerCharacter == nullptr)
			return;
		UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(m_OwnerCharacter->GetGameInstance());
		if (GameInstance == nullptr)
			return;

		FItem* LoadItem = new FItem();
		//ItemTableInfo 설정.
		if (InventoryData[i] == 0)
			return;
		LoadItem->ItemTableInfo = GameInstance->FindItemTableInfo(*(int*)&InventoryData[i]);
		i += sizeof(int);
		//ItemCount 설정
		LoadItem->Count = static_cast<int>(*(int*)&InventoryData[i]);
		i += sizeof(int);

		//인벤토리에 추가.
		m_ItemArray.Add(LoadItem);
		SetUI(LoadItem);
	}
}
