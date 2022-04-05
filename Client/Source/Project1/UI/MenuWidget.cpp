// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "MainHUDWidget.h"
#include "MenuCommonWidget.h"
#include "Inventory/InventoryWidget.h"
#include "Bullet/BulletWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Project1/Player/PlayerCharacter.h"
#include "MenuCommonWidget.h"
#include "QuickSlotsWidget.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Project1GameModeBase.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	m_InventoryButton = Cast<UButton>(GetWidgetFromName(TEXT("InventoryButton")));
	m_BulletButton = Cast<UButton>(GetWidgetFromName(TEXT("BulletButton")));
	m_MapButton = Cast<UButton>(GetWidgetFromName(TEXT("MapButton")));
	m_SettingButton = Cast<UButton>(GetWidgetFromName(TEXT("SettingButton")));
	
	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	m_MenuCommonWidget = Cast<UMenuCommonWidget>(GetWidgetFromName(TEXT("UI_MenuCommon")));
	m_InventoryWidget = Cast<UInventoryWidget>(GetWidgetFromName(TEXT("UI_Inventory")));
	m_BulletWidget = Cast<UBulletWidget>(GetWidgetFromName(TEXT("UI_Bullet")));
	// m_MapMainWidget = Cast<UInventoryMainWidget>(GetWidgetFromName(TEXT("InventoryButton")));
	// m_SettingMainWidget = Cast<UInventoryMainWidget>(GetWidgetFromName(TEXT("InventoryButton")));
	
	
	m_InventoryButton->OnClicked.AddDynamic(this, &UMenuWidget::InventoryButtonClick);
	m_BulletButton->OnClicked.AddDynamic(this, &UMenuWidget::BulletButtonClick);
	m_MapButton->OnClicked.AddDynamic(this, &UMenuWidget::MapButtonClick);
	m_SettingButton->OnClicked.AddDynamic(this, &UMenuWidget::SettingButtonClick);

	m_CloseButton->OnClicked.AddDynamic(this, &UMenuWidget::CloseButtonClick);
	m_IsOpen = false;

	//스왑을 위한 이전 위젯/버튼 저장.
	m_PrevButton = m_InventoryButton;
	m_PrevWidget = m_InventoryWidget;

	//퀵슬롯 드래그&드랍을위한 변수

	m_QuickSlotObj = nullptr;
	m_QuickSlotType= EQuickSlotType::None;

}

void UMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UMenuWidget::SetQuickSlotObj(EQuickSlotType QuickSlotType, FQuickSlotObj* Obj)
{
	AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameModeBase)
	{
		UMainHUDWidget* MainHUDWidget = GameModeBase->GetMainHUDWidget();
		if(MainHUDWidget)
		{
			UQuickSlotsWidget* QuickSlotsWidget = MainHUDWidget->GetQuickSlotWidget();
			if(QuickSlotsWidget)
			{
				m_QuickSlotType = QuickSlotType;
				m_QuickSlotObj = Obj;
				
				//QucikSlot 반짝이게 만들기.
				switch (m_QuickSlotType)
				{
				case EQuickSlotType::None :
					QuickSlotsWidget->QuickItemSlotOn(false);
					QuickSlotsWidget->QuickBulletSlotOn(false);
					break;
				case EQuickSlotType::Item :
					QuickSlotsWidget->QuickItemSlotOn(true);
					break;
				case EQuickSlotType::Bullet :
					QuickSlotsWidget->QuickBulletSlotOn(true);
					break;
				}
			}
		}
	}
}

void UMenuWidget::InventoryButtonClick()
{
	if(m_PrevWidget != m_InventoryWidget)
	{
		if(m_InventoryWidget)
		{
			m_InventoryButton->SetColorAndOpacity(FLinearColor(1.f,1.f,1.f,2.f));
			m_InventoryWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

			m_MenuCommonWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			
			//이전 버튼,위젯 비활성화.
			m_PrevButton->SetColorAndOpacity(FLinearColor(1.f,1.f,1.f,0.5f));
			m_PrevWidget->SetVisibility(ESlateVisibility::Collapsed);
			m_PrevButton = m_InventoryButton;
			m_PrevWidget = m_InventoryWidget;
		}
	}
}

void UMenuWidget::BulletButtonClick()
{
	if(m_PrevWidget != m_BulletWidget)
	{
		if(m_InventoryWidget)
		{
			m_BulletButton->SetColorAndOpacity(FLinearColor(1.f,1.f,1.f,2.f));
			m_BulletWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

			m_MenuCommonWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			
			//이전 버튼,위젯 비활성화.
			m_PrevButton->SetColorAndOpacity(FLinearColor(1.f,1.f,1.f,0.5f));
			m_PrevWidget->SetVisibility(ESlateVisibility::Collapsed);
			m_PrevButton = m_BulletButton;
			m_PrevWidget = m_BulletWidget;
		}
	}
}

void UMenuWidget::MapButtonClick()
{
	// if(m_MapMainWidget)
	// {
	// 	//m_MapMainWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	// }
}

void UMenuWidget::SettingButtonClick()
{
	// if(m_SettingMainWidget)
	// {
	// 	//m_SettingMainWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	// }
}

void UMenuWidget::CloseButtonClick()
{
	SetVisibility(ESlateVisibility::Collapsed);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
		PlayerController->bShowMouseCursor = false;
	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerController->GetCharacter());
	if(Player)
		Player->SetIsUIMode(false);
}