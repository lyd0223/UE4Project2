// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"

#include "Door.h"
#include "../Trigger/RoomTrigger.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Project1GameModeBase.h"
#include "Project1/Monster/SpawnPoint.h"
#include "Project1/UI/MainHUDWidget.h"
#include "Project1/Map/LootBox.h"

// Sets default values
ARoom::ARoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	m_BoxComponent->SetupAttachment(GetRootComponent());
	m_BoxComponent->SetCollisionProfileName(TEXT("Room"));

	m_RoomTrigger = nullptr;

	m_IsClear = false;
	m_MonsterCount = 0;

	static ConstructorHelpers::FClassFinder<ALootBox> LootBoxAsset(
		TEXT("Blueprint'/Game/01Resources/Map/BPLootBox.BPLootBox_C'"));
	if (LootBoxAsset.Succeeded())
		m_LootBoxClass = LootBoxAsset.Class;
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();


	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	m_RoomTrigger = GetWorld()->SpawnActor<ARoomTrigger>(ARoomTrigger::StaticClass(), GetActorLocation(),
	                                                     GetActorRotation(), param);
	m_RoomTrigger->SetTriggerSize(FVector(900.f, 900.f, 500.f));
	m_RoomTrigger->SetOwnerRoom(this);

	m_MonsterCount = m_SpawnPointArray.Num();

	for (auto SpawnPoint : m_SpawnPointArray)
	{
		SpawnPoint->SetOwnerRoom(this);
	}

	//GetWorld()->GetTimerManager().SetTimer(m_RegisterTimerHandle, this, &ARoom::RegisterRoomintoMinimap, 0.5f, false, 0.5f);
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARoom::DeductMonsterCount()
{
	m_MonsterCount--;
	if (m_MonsterCount <= 0 && m_IsClear == false)
	{
		m_IsClear = true;
		Clear();
	}
}

void ARoom::Clear()
{
	for (auto Door : m_DoorArray)
	{
		Door->Open();
	}


	//보상상자 스폰
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ALootBox* LootBox = GetWorld()->SpawnActor<ALootBox>(m_LootBoxClass, GetActorLocation(), GetActorRotation(), param);
}

void ARoom::Enter()
{
	if (!m_IsClear)
	{
		for (auto Door : m_DoorArray)
		{
			Door->Close();
		}
		for (auto SpawnPoint : m_SpawnPointArray)
		{
			SpawnPoint->SpawnMonster();
		}
	}
}

// void ARoom::RegisterRoomintoMinimap()
// {
// 	//미니맵에 등록
// 	AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
// 	if(GameModeBase)
// 	{
// 		UMainHUDWidget* MainHUDWidget = GameModeBase->GetMainHUDWidget();\
// 		if(MainHUDWidget)
// 		{
// 			UMinimapWidget* MinimapWidget = MainHUDWidget->GetMinimapWidget();
// 			MinimapWidget->AddRoomArray(this);
// 			//MinimapWidget->SetRoomImage(this);
// 		}
// 	}
// }
