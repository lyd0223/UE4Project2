// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "WaitingRoomMainWidget.generated.h"

UCLASS()
class PROJECT1_API UWaitingRoomMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStoreMainWidget* m_StoreMainWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class URelicMainWidget* m_RelicMainWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_CloseButton;
	
	public:
	class UStoreMainWidget* GetStoreMainWidget() const
	{
		return m_StoreMainWidget;
	}
	class URelicMainWidget* GetRelicMainWidget() const
	{
		return m_RelicMainWidget;
	}
	
	protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	public:
	UFUNCTION()
	void CloseButtonClicked();
};
