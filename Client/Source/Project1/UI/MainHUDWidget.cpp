#include "MainHUDWidget.h"

#include "Components/CanvasPanelSlot.h"


void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_PlayerHUDWidget = Cast<UPlayerHUDWidget>(GetWidgetFromName(TEXT("UI_PlayerState")));
	m_BuffMainWidget = Cast<UBuffMainWidget>(GetWidgetFromName(TEXT("UI_BuffMain")));
	m_MonsterStateWidget = Cast<UMonsterStateWidget>(GetWidgetFromName(TEXT("UI_MonsterState")));
	m_MinimapWidget = Cast<UMinimapWidget>(GetWidgetFromName(TEXT("UI_MinimapWidget")));
	m_QuickSlotWidget = Cast<UQuickSlotsWidget>(GetWidgetFromName(TEXT("UI_QuickSlots")));
	m_MenuWidget = Cast<UMenuWidget>(GetWidgetFromName(TEXT("UI_Menu")));
	m_LootHUD = Cast<ULootHUDWidget>(GetWidgetFromName(TEXT("UI_LootHUD")));
}

void UMainHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}
