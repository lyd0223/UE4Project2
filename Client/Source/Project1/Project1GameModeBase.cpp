// Copyright Epic Games, Inc. All Rights Reserved.


#include "Project1GameModeBase.h"

#include "Project1GameInstance.h"
#include "AssetManager/AssetPathLoader.h"
#include "Manager/InventoryManager.h"
#include "UI/MainHUDWidget.h"
#include "UI/MenuCommonWidget.h"
#include "UI/Bullet/BulletListItemData.h"
#include "UI/Bullet/BulletWidget.h"

AProject1GameModeBase::AProject1GameModeBase()
{
	//직업정보
	static ConstructorHelpers::FClassFinder<APawn> GunnerPawnClass(TEXT("Blueprint'/Game/01Resources/Player/Gunner/BPGunner.BPGunner_C'"));
	if(GunnerPawnClass.Succeeded())
		m_PlayerClassArray.Add(GunnerPawnClass.Class);
	static ConstructorHelpers::FClassFinder<APawn> BelicaPawnClass(TEXT("Blueprint'/Game/01Resources/Player/Belica/BPBelica.BPBelica_C'"));
	if(BelicaPawnClass.Succeeded())
		m_PlayerClassArray.Add(BelicaPawnClass.Class);
	static ConstructorHelpers::FClassFinder<APawn> RevenantPawnClass(TEXT("Blueprint'/Game/01Resources/Player/Gunner/BPGunner.BPGunner_C'"));
	if(RevenantPawnClass.Succeeded())
		m_PlayerClassArray.Add(RevenantPawnClass.Class);
	

	//MainHUDWidget
	static ConstructorHelpers::FClassFinder<UMainHUDWidget>	MainHUDWidgetClass(TEXT("WidgetBlueprint'/Game/01Resources/UI/UI_MainHUD.UI_MainHUD_C'"));
	if (MainHUDWidgetClass.Succeeded())
		m_MainHUDWidgetClass = MainHUDWidgetClass.Class;
}

void AProject1GameModeBase::InitGame(const FString& MapName, 
	const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	//직업정보 로드
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance)
	{
		EPlayerJob SelectJob = GameInstance->GetSelectJob();

		switch (SelectJob)
		{
		case EPlayerJob::Gunner:
			{
				DefaultPawnClass = m_PlayerClassArray[0];
			}
			break;
		case EPlayerJob::Belica:
			{
				DefaultPawnClass = m_PlayerClassArray[1];
			}
			break;
		case EPlayerJob::Revenant:
			{
				DefaultPawnClass = m_PlayerClassArray[2];
			}
			break;
		}
	}

	
	//Asset비동기로드를 위해 AssetPathLoader 활성화
	m_AssetPathLoader = UAssetPathLoader::StaticClass()->GetDefaultObject<UAssetPathLoader>();
	m_AssetPathLoader->ConvertPath();
}

void AProject1GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Widget Add to Viewport 
	if (IsValid(m_MainHUDWidgetClass))
	{
		m_MainHUDWidget = Cast<UMainHUDWidget>(CreateWidget(GetWorld(), m_MainHUDWidgetClass));

		if (m_MainHUDWidget)
		{
			m_MainHUDWidget->AddToViewport();

			//이전에 있던 인벤토리를 넘겨주기위함.
			UInventoryWidget* InventoryWidget = m_MainHUDWidget->GetMenuWidget()->GetInventoryWidget();
			InventoryWidget->SetOwnerGameModeBase(this);
			//UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());
			//InventoryWidget->Refresh(GameInstance->GetInventoryManager()->GetItemArray());

			UBulletWidget* BulletWidget = m_MainHUDWidget->GetMenuWidget()->GetBulletWidget();
			UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetGameInstance());
			
			FBullet* Bullet1 = new FBullet();
			Bullet1->BulletTableInfo = GameInstance->FindBulletTableInfo(TEXT("NormalBullet"));
			UBulletListItemData* BulletListItemData1 = NewObject<UBulletListItemData>(this, UBulletListItemData::StaticClass());
			BulletListItemData1->SetBullet(Bullet1);
			BulletWidget->AddBulletListView(BulletListItemData1);
			FBullet* Bullet2 = new FBullet();
			Bullet2->BulletTableInfo = GameInstance->FindBulletTableInfo(TEXT("TrippleBullet"));
			UBulletListItemData* BulletListItemData2 = NewObject<UBulletListItemData>(this, UBulletListItemData::StaticClass());
			BulletListItemData2->SetBullet(Bullet2);
			BulletWidget->AddBulletListView(BulletListItemData2);
			FBullet* Bullet3 = new FBullet();
			Bullet3->BulletTableInfo = GameInstance->FindBulletTableInfo(TEXT("RecoveryBullet"));
			UBulletListItemData* BulletListItemData3 = NewObject<UBulletListItemData>(this, UBulletListItemData::StaticClass());
			BulletListItemData3->SetBullet(Bullet3);
			BulletWidget->AddBulletListView(BulletListItemData3);
			FBullet* Bullet4 = new FBullet();
			Bullet4->BulletTableInfo = GameInstance->FindBulletTableInfo(TEXT("PowerBullet"));
			UBulletListItemData* BulletListItemData4 = NewObject<UBulletListItemData>(this, UBulletListItemData::StaticClass());
			BulletListItemData4->SetBullet(Bullet4);
			BulletWidget->AddBulletListView(BulletListItemData4);
		}
	}

	//InputMode
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	FInputModeGameOnly	Mode;
	Controller->SetInputMode(Mode);
	Controller->bShowMouseCursor = false;
}
