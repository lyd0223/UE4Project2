// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "StoreWidget.generated.h"

UCLASS()
class PROJECT1_API UStoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UListView* m_StoreListView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBuyWidget* m_BuyWidget;

public:
	class UBuyWidget* GetBuyWidget() const
	{
		return m_BuyWidget;
	}
	void SetBuyWidget(class UBuyWidget* _BuyWidget)
	{
		m_BuyWidget = _BuyWidget;
	}
	
protected:
	virtual void NativeConstruct() override;

public:
	void AddItemSaleItemListView(FItem* Item);
};
