// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "StoreMainWidget.generated.h"

UCLASS()
class PROJECT1_API UStoreMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStoreWidget* m_StoreWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UInventoryWidget* m_InventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_CloseButton;

public:
	class UStoreWidget* GetStoreWidget() const
	{
		return m_StoreWidget;
	}

	class UInventoryWidget* GetInventoryWidget() const
	{
		return m_InventoryWidget;
	}

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void CloseButtonClicked();
};
