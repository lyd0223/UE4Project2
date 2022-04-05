// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "QuickItemSlotWidget.generated.h"

UCLASS()
class PROJECT1_API UQuickItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* m_ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_CountText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_LabelText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_SlotButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* m_SelectImage;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	uint8 m_LabelIndex;

	FItem* m_Item;

	public:
	FItem* GetItem() const
	{
		return m_Item;
	}
	void SetItem(FItem* Item)
	{
		m_Item = Item;
	}
	
	protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	public:
	UFUNCTION()
	void SlotButtonHovered();
	UFUNCTION()
	void SlotButtonClicked();
	
	//깜빡임을 키고 끄는 함수.
	void SelectImageOn()
	{
		m_SelectImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	void SelectImageOff()
	{
		m_SelectImage->SetVisibility(ESlateVisibility::Collapsed);
	}

	//슬롯 새로고침.
	void SlotRefresh(uint32 Count);
};
