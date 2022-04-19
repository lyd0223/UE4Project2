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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//class UChatWidget* m_ChatWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UMenuWidget* m_MenuWidget;
	
	public:
	class UStoreMainWidget* GetStoreMainWidget() const
	{
		return m_StoreMainWidget;
	}
	class URelicMainWidget* GetRelicMainWidget() const
	{
		return m_RelicMainWidget;
	}
	class UMenuWidget* GetMenuWidget() const
	{
		return m_MenuWidget;
	}
	
	protected:
	virtual void NativeConstruct() override;

	public:
};
