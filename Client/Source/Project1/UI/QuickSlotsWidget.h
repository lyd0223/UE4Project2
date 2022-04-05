// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlotsWidget.generated.h"


UENUM(BlueprintType)
enum class EQuickBulletSlotChangeType : uint8
{
	Left,
	Right
	
};

UCLASS()
class PROJECT1_API UQuickSlotsWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class UQuickBulletSlotWidget*> m_QuickBulletSlotWidgetArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class UQuickItemSlotWidget*> m_QuickItemSlotWidgetArray;

	public:
	class UQuickItemSlotWidget* GetQuickItemSlotWidget(uint8 Index) const
	{
		return m_QuickItemSlotWidgetArray[Index];
	}
	class UQuickBulletSlotWidget* GetQuickBulletSlotWidget(uint8 Index) const
	{
		return m_QuickBulletSlotWidgetArray[Index];
	}
	
	protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	
	public:
	void QuickBulletSlotOn(bool IsOn);
	void QuickItemSlotOn(bool IsOn);
	void QuickBulletSlotChange(EQuickBulletSlotChangeType ChangeType, uint8 Index);
	void RefreshItems(FItem* Item);
	
};
