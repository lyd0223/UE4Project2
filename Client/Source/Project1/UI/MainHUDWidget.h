// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "PlayerHUDWidget.h"
#include "MenuWidget.h"
#include "MonsterStateWidget.h"
#include "QuickSlotsWidget.h"
#include "Inventory/InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Buff/BuffMainWidget.h"
#include "Loot/LootHUDWidget.h"
#include "Minimap/MinimapWidget.h"
#include "MainHUDWidget.generated.h"

UCLASS()
class PROJECT1_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPlayerHUDWidget* m_PlayerHUDWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBuffMainWidget* m_BuffMainWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMonsterStateWidget* m_MonsterStateWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMinimapWidget* m_MinimapWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UQuickSlotsWidget* m_QuickSlotWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMenuWidget* m_MenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ULootHUDWidget* m_LootHUD;
	
public:
	UPlayerHUDWidget* GetPlayerHUDWidget() const
	{
		return m_PlayerHUDWidget;
	}

	UBuffMainWidget* GetBuffMainWidget() const
	{
		return m_BuffMainWidget;
	}
	
	UMonsterStateWidget* GetMonsterStateWidget() const
	{
		return m_MonsterStateWidget;
	}
	
	UMinimapWidget* GetMinimapWidget() const
	{
		return m_MinimapWidget;
	}
	
	UQuickSlotsWidget* GetQuickSlotWidget() const
	{
		return m_QuickSlotWidget;
	}

	UMenuWidget* GetMenuWidget() const
	{
		return m_MenuWidget;
	}

	ULootHUDWidget* GetLootHUD() const
	{
		return m_LootHUD;
	}
	
	void SetQuickSlotsWidget(UQuickSlotsWidget* QuickSlotsWidget)
	{
		m_QuickSlotWidget = QuickSlotsWidget;
	}
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
