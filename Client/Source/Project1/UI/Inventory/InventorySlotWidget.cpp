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

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	m_CountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CountText")));
	m_ItemButton = Cast<UButton>(GetWidgetFromName(TEXT("ItemButton")));
	m_ItemCanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("ItemCanvasPanel")));
	
	m_Item = nullptr;
	
	if(!m_Item)
	{
		m_ItemImage->SetBrushFromTexture(nullptr);
		m_ItemCanvasPanel->SetVisibility(ESlateVisibility::Collapsed);
	}

	m_ItemButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::ItemButtonClicked);
	m_ItemButton->OnHovered.AddDynamic(this, &UInventorySlotWidget::ItemButtonHovered);
	m_ItemButton->OnUnhovered.AddDynamic(this, &UInventorySlotWidget::ItemButtonUnHovered);

	
}

void UInventorySlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

FReply UInventorySlotWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	
	if (m_ItemButton->IsHovered())
	{
		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(m_ItemToolTipWidget->Slot);

		if (PanelSlot)
		{
			FVector2D	WidgetPos = InMouseEvent.GetScreenSpacePosition();
			
			// 마우스의 Screen좌표를 위젯의 Local 좌표로 변경
			WidgetPos = InGeometry.AbsoluteToLocal(WidgetPos);

			UUniformGridSlot* GridSlot = Cast<UUniformGridSlot>(Slot);
			WidgetPos.X += (GridSlot->Column * 100.f);
			WidgetPos.Y += (GridSlot->Row * 100.f);

			WidgetPos.Y += 100.f;
			
			PanelSlot->SetPosition(WidgetPos);

			//PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("X : %.5f Y : %.5f"), WidgetPos.X, WidgetPos.Y));
		}
	}

	
	return FReply::Handled();
}

void UInventorySlotWidget::ItemButtonClicked()
{
	//PrintViewport(2.f, FColor::Yellow, "ItemButtonClicked");

	//m_IsDrag = true;
	if(m_Item)
	{
		AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
		if(GameModeBase)
		{
			UMainHUDWidget* MainHUDWidget = GameModeBase->GetMainHUDWidget();
			if(MainHUDWidget)
			{
				UMenuWidget* MenuWidget	= MainHUDWidget->GetMenuWidget();
				MenuWidget->SetQuickSlotObj(EQuickSlotType::Item, m_Item);

				FVector Loc = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
				FActorSpawnParameters param;
				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), Loc,
					FRotator::ZeroRotator, param);
				Effect->LoadSoundAsync(TEXT("Click"));
				Effect->SetLifeTime(1.f);
			}
		}
	}
}

void UInventorySlotWidget::ItemButtonReleased()
{
	//PrintViewport(2.f, FColor::Yellow, "ItemButtonReleased");

	m_IsDrag = false;
}

void UInventorySlotWidget::ItemButtonHovered()
{
	if(m_Item)
	{
		//PrintViewport(2.f, FColor::Blue, "ItemButtonHovered");
		m_ItemToolTipWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_ItemToolTipWidget->SetDatas(*m_Item);
	}
}

void UInventorySlotWidget::ItemButtonUnHovered()
{
	//PrintViewport(2.f, FColor::Blue, "ItemButtonUnHovered");
	m_ItemToolTipWidget->SetVisibility(ESlateVisibility::Collapsed);
}


void UInventorySlotWidget::SetDatas(FItem* Item)
{
	m_Item = Item;
	m_ItemImage->SetBrushFromTexture(m_Item->ItemTableInfo->IconTexture);
	m_CountText->SetText(FText::FromString(FString::Printf(TEXT("%d"),m_Item->Count)));
	m_ItemCanvasPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

