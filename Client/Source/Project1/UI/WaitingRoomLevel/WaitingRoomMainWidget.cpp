// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingRoomMainWidget.h"
#include "Store/StoreMainWidget.h"
#include "Project1/UI/MenuWidget.h"
#include "Project1/UI/WaitingRoomLevel/Chat/ChatWidget.h"

void UWaitingRoomMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_StoreMainWidget = Cast<UStoreMainWidget>(GetWidgetFromName(TEXT("UI_StoreMain")));
	m_RelicMainWidget = nullptr;
	m_ChatWidget = Cast<UChatWidget>(GetWidgetFromName(TEXT("UI_ChatWidget")));
	m_MenuWidget = Cast<UMenuWidget>(GetWidgetFromName(TEXT("UI_Menu")));
}



