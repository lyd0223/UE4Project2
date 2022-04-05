// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_GoldText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_WeightText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUniformGridPanel* m_InventoryPanel;

	class UItemToolTipWidget* m_ItemToolTipWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class UInventorySlotWidget*> m_SlotArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UInventorySlotWidget> m_InventorySlotWidgetClass;

	AGameModeBase* m_OwnerGameModeBase;
	
public:
	void SetOwnerGameModeBase(AGameModeBase* GameModeBase)
	{
		m_OwnerGameModeBase = GameModeBase;
	}
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void Refresh(TArray<FItem*>& ItemArray);
	void AddItem(FItem* Item);
	void AddInventorySlot();
	void DeductItemCount(FItem* Item);
};
