// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventorySlotWidget.generated.h"

UCLASS()
class PROJECT1_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* m_ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_CountText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_ItemButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCanvasPanel* m_ItemCanvasPanel;

	class UItemToolTipWidget* m_ItemToolTipWidget;

	FItem* m_Item;

	float m_CursorPosX, m_CursorPosY;

	bool m_IsDrag;

public :
	void SetItemToolTipWidget(class UItemToolTipWidget* ItemToolTipWidget)
	{
		m_ItemToolTipWidget = ItemToolTipWidget;
	}

	FItem* GetItem() const
	{
		return m_Item;
	}

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


public:
	UFUNCTION()
	void ItemButtonClicked();
	UFUNCTION()
	void ItemButtonReleased();
	UFUNCTION()
	void ItemButtonHovered();
	UFUNCTION()
	void ItemButtonUnHovered();

	void SetDatas(FItem* Item);
};
