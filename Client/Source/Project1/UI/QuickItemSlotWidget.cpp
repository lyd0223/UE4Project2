// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickItemSlotWidget.h"

#include "MainHUDWidget.h"
#include "MenuWidget.h"
#include "WidgetDragDropOperation.h"
#include "Project1/Project1GameModeBase.h"
#include "Project1/Effect/NormalEffect.h"
#include "Project1/Player/PlayerCharacter.h"
#include "Project1/UI/Inventory/InventorySlotWidget.h"

void UQuickItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	m_CountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CountText")));
	m_LabelText = Cast<UTextBlock>(GetWidgetFromName(TEXT("LabelText")));
	m_SelectImage = Cast<UImage>(GetWidgetFromName(TEXT("SelectImage")));

	m_LabelText->SetText(FText::FromString(FString::FromInt(m_LabelIndex + 1)));

	m_ItemImage->SetBrushFromTexture(nullptr);
	m_ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	m_CountText->SetVisibility(ESlateVisibility::Collapsed);

	m_Item = nullptr;
}

void UQuickItemSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

bool UQuickItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                        UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UWidgetDragDropOperation* DDOper = Cast<UWidgetDragDropOperation>(InOperation);
	if (DDOper == nullptr)
		return false;

	//퀵슬롯 이펙트 끄기
	m_QuickSlotsWidget->QuickItemSlotOn(false);
	
	//퀵슬롯에 추가.
	UInventorySlotWidget* InventorySlotWidget = Cast<UInventorySlotWidget>(DDOper->GetWidget());
	if (InventorySlotWidget == nullptr)
		return false;
	m_Item = InventorySlotWidget->GetItem();
	m_ItemImage->SetBrushFromTexture(m_Item->ItemTableInfo->IconTexture);
	m_CountText->SetText(FText::FromString(FString::FromInt(m_Item->Count)));

	m_ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	m_CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	//PlayerCharacter QuickSlotArray변경
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	Player->SetItemQuickSlot(m_LabelIndex, m_Item);

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(
		ANormalEffect::StaticClass(), Player->GetActorLocation(),
		FRotator::ZeroRotator, param);
	Effect->LoadSoundAsync(TEXT("Click"));
	Effect->SetLifeTime(1.f);
	
	return true;
}

void UQuickItemSlotWidget::SlotRefresh(uint32 Count)
{
	if (Count == 0)
	{
		m_ItemImage->SetBrushFromTexture(nullptr);
		m_CountText->SetText(FText::FromString(FString::FromInt(Count)));

		m_ItemImage->SetVisibility(ESlateVisibility::Collapsed);
		m_CountText->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		m_CountText->SetText(FText::FromString(FString::FromInt(Count)));
	}
}
