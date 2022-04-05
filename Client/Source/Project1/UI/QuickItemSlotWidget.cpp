// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickItemSlotWidget.h"

#include "MainHUDWidget.h"
#include "MenuWidget.h"
#include "Project1/Project1GameModeBase.h"
#include "Project1/Effect/NormalEffect.h"
#include "Project1/Player/PlayerCharacter.h"

void UQuickItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	m_CountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CountText")));
	m_LabelText = Cast<UTextBlock>(GetWidgetFromName(TEXT("LabelText")));
	m_SlotButton = Cast<UButton>(GetWidgetFromName(TEXT("SlotButton")));
	m_SelectImage = Cast<UImage>(GetWidgetFromName(TEXT("SelectImage")));
	
	m_SlotButton->OnHovered.AddDynamic(this, &UQuickItemSlotWidget::SlotButtonHovered);
	m_SlotButton->OnClicked.AddDynamic(this, &UQuickItemSlotWidget::SlotButtonClicked);
	
	
	m_LabelText->SetText(FText::FromString(FString::FromInt(m_LabelIndex+1)));

	m_ItemImage->SetBrushFromTexture(nullptr);
	m_ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	m_CountText->SetVisibility(ESlateVisibility::Collapsed);

	m_Item = nullptr;
}

void UQuickItemSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}


void UQuickItemSlotWidget::SlotButtonHovered()
{
	//PrintViewport(2.f, FColor::Blue, "SlotButtonHovered");
}

void UQuickItemSlotWidget::SlotButtonClicked()
{
	//PrintViewport(2.f, FColor::Blue, "SlotButtonClicked");

	AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
	if(IsValid(GameModeBase))
	{
		UMainHUDWidget* MainHUDWidget = GameModeBase->GetMainHUDWidget();
		if(MainHUDWidget)
		{
			UMenuWidget* MenuWidget= MainHUDWidget->GetMenuWidget();
			EQuickSlotType QuickSlotType = MenuWidget->GetQuickSlotType();
			
			if(QuickSlotType == EQuickSlotType::Item)
			{
				FItem* Item = (FItem*)(MenuWidget->GetQuickSlotObj());
				if(Item)
				{
					m_Item = Item;
					m_ItemImage->SetBrushFromTexture(Item->ItemTableInfo->IconTexture);
					m_CountText->SetText(FText::FromString(FString::FromInt(Item->Count)));

					m_ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					m_CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

					MenuWidget->SetQuickSlotObj(EQuickSlotType::None, nullptr);


					//PlayerCharacter QuickSlotArray변경
					APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
					Player->SetItemQuickSlot(m_LabelIndex, Item);

					FActorSpawnParameters param;
					param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), Player->GetActorLocation(),
						FRotator::ZeroRotator, param);
					Effect->LoadSoundAsync(TEXT("Click"));
					Effect->SetLifeTime(1.f);
				}
			}
		}
		
	}
}

void UQuickItemSlotWidget::SlotRefresh(uint32 Count)
{
	if(Count == 0)
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