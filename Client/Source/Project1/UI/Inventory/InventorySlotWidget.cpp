// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"

#include "ItemToolTipWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/UniformGridSlot.h"
#include "Project1/Project1GameModeBase.h"
#include "Project1/Effect/NormalEffect.h"
#include "Project1/UI/MainHUDWidget.h"
#include "Project1/UI/MenuWidget.h"
#include "Project1/UI/WidgetDragDropOperation.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	m_CountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CountText")));
	m_ItemCanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("ItemCanvasPanel")));
	
	m_Item = nullptr;
	
	if(!m_Item)
	{
		m_ItemImage->SetBrushFromTexture(nullptr);
		m_ItemCanvasPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UInventorySlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

FReply UInventorySlotWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	
	UCanvasPanelSlot* ItemToolTipPanelSlot = Cast<UCanvasPanelSlot>(m_ItemToolTipWidget->Slot);
	if(ItemToolTipPanelSlot == nullptr)
		return FReply::Unhandled();
	FVector2D CursorPos = InMouseEvent.GetScreenSpacePosition();
	ItemToolTipPanelSlot->SetPosition(USlateBlueprintLibrary::AbsoluteToLocal(m_OwnerWidget->GetCachedGeometry(), CursorPos));
	
	return FReply::Handled();
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FVector Loc = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
	FActorSpawnParameters param;
	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), Loc,
					FRotator::ZeroRotator, param);
	Effect->LoadSoundAsync(TEXT("Click"));
	Effect->SetLifeTime(1.f);
	
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, FKey("LeftMouseButton"));
	return Reply.NativeReply;
}

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(m_Item)
	{
		//PrintViewport(2.f, FColor::Blue, "ItemButtonHovered");
		m_ItemToolTipWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_ItemToolTipWidget->SetDatas(*m_Item);
		
		// UCanvasPanelSlot* ItemToolTipPanelSlot = Cast<UCanvasPanelSlot>(m_ItemToolTipWidget->Slot);
		// if(ItemToolTipPanelSlot == nullptr)
		//  	return;
		// UUniformGridSlot* PanelSlot = Cast<UUniformGridSlot>(Slot);
		// if(PanelSlot == nullptr)
		// 	return;
		// FVector2D Pos = USlateBlueprintLibrary::LocalToAbsolute(this->GetCachedGeometry(),this->GetCachedGeometry().Position);
		//
		// ItemToolTipPanelSlot->SetPosition(USlateBlueprintLibrary::AbsoluteToLocal(m_ItemToolTipWidget->GetCachedGeometry(),Pos));
	}
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	m_ItemToolTipWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventorySlotWidget::NativeOnDragDetected(
	const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//????????? ????????? ??????.
	AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameModeBase == nullptr)
		return;
	UMainHUDWidget* MainHUDWidget = GameModeBase->GetMainHUDWidget();
	if (MainHUDWidget == nullptr)
		return;
	UQuickSlotsWidget* QuickSlotsWidget = MainHUDWidget->GetQuickSlotWidget();
	if(QuickSlotsWidget == nullptr)
		return;
	QuickSlotsWidget->QuickItemSlotOn(true);

	//DragDropOperation ??????.
	UWidgetDragDropOperation* DDOper =
		Cast<UWidgetDragDropOperation>(
			UWidgetBlueprintLibrary::CreateDragDropOperation(UWidgetDragDropOperation::StaticClass()));
	if(DDOper == nullptr)
		return;
	DDOper->SetWidget(this);
	DDOper->SetMousePosition(InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()));
	DDOper->DefaultDragVisual = m_ItemImage;
	DDOper->Pivot = EDragPivot::MouseDown;

	OutOperation = DDOper;
	
	//m_ItemImage->RemoveFromParent();
	//m_ItemImage->SetVisibility(ESlateVisibility::Collapsed);
}

//void UInventorySlotWidget::ItemButtonClicked()
//{
	//
	// if(m_Item)
	// {
	// 	AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
	// 	if(GameModeBase)
	// 	{
	// 		UMainHUDWidget* MainHUDWidget = GameModeBase->GetMainHUDWidget();
	// 		if(MainHUDWidget)
	// 		{
	// 			UMenuWidget* MenuWidget	= MainHUDWidget->GetMenuWidget();
	// 			MenuWidget->SetQuickSlotObj(EQuickSlotType::Item, m_Item);
	//
	// 			FVector Loc = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
	// 			FActorSpawnParameters param;
	// 			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// 			ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), Loc,
	// 				FRotator::ZeroRotator, param);
	// 			Effect->LoadSoundAsync(TEXT("Click"));
	// 			Effect->SetLifeTime(1.f);
	// 		}
	// 	}
	// }
//}

void UInventorySlotWidget::SetDatas(FItem* Item)
{
	m_Item = Item;
	m_ItemImage->SetBrushFromTexture(m_Item->ItemTableInfo->IconTexture);
	m_CountText->SetText(FText::FromString(FString::Printf(TEXT("%d"),m_Item->Count)));
	m_ItemCanvasPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

