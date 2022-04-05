// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MenuWidget.generated.h"

UENUM(BlueprintType)
enum class EQuickSlotType : uint8
{
	None,
	Item,
	Bullet,
};

UCLASS()
class PROJECT1_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_InventoryButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_BulletButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_MapButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_SettingButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_CloseButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UMenuCommonWidget* m_MenuCommonWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UInventoryWidget* m_InventoryWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBulletWidget* m_BulletWidget;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// class UMapMainWidget* m_MapMainWidget;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// class USettingMainWidget* m_SettingMainWidget;

	//퀵슬롯 설정을위한 FItem / FBullet / EDragType
	FQuickSlotObj* m_QuickSlotObj;
	EQuickSlotType m_QuickSlotType;
	
	
	bool m_IsOpen;
	UUserWidget* m_PrevWidget;
	UButton*	 m_PrevButton;
	
public:
	bool GetIsOpen() const
	{
		return m_IsOpen;
	}
	class UMenuCommonWidget* GetMenuCommonWidget() const
	{
		return m_MenuCommonWidget;
	}
	class UInventoryWidget* GetInventoryWidget() const
	{
		return m_InventoryWidget;
	}
	class UBulletWidget* GetBulletWidget() const
	{
		return m_BulletWidget;
	}
	EQuickSlotType GetQuickSlotType() const
	{
		return m_QuickSlotType;
	}
	FQuickSlotObj* GetQuickSlotObj() const
	{
		return m_QuickSlotObj;
	}
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
public:
	void SetQuickSlotObj(EQuickSlotType QuickSlotType, FQuickSlotObj* Obj);
	
	UFUNCTION()
	void InventoryButtonClick();
	UFUNCTION()
	void BulletButtonClick();
	UFUNCTION()
	void MapButtonClick();
	UFUNCTION()
	void SettingButtonClick();
	UFUNCTION()
	void CloseButtonClick();
	
};
