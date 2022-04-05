// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "BuffSlotWidget.generated.h"

UCLASS()
class PROJECT1_API UBuffSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* m_BuffImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* m_CooldownImage;

	const FItemTableInfo* m_ItemTableInfo;
	
	UPROPERTY()
	UMaterialInstanceDynamic* m_MTInstDynamic;
	
	int32		m_Index;

	bool m_IsActive;
	
	float m_Time;
	float m_AccTime;

	class UBuffMainWidget* m_OwnerBuffMainWidget;

	public:
	const FItemTableInfo* GetItemTableInfo() const
	{
		return m_ItemTableInfo;
	}
	
	int32 GetIndex()	const
	{
		return m_Index;
	}
	void SetIndex(int32 Index)
	{
		m_Index = Index;
	}

	bool GetIsActive() const
	{
		return m_IsActive;
	}
	void SetIsActive(bool IsActive)
	{
		m_IsActive = IsActive;
	}

	float GetTime() const
	{
		return m_Time;
	}
	float GetAccTime() const
	{
		return m_AccTime;
	}
	
	void SetOwnerBuffMainWidget(UBuffMainWidget* BuffMainWidget)
	{
		m_OwnerBuffMainWidget = BuffMainWidget;
	}

	protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void BuffSlotReset();
	
	public:
	void BuffStart(const FItemTableInfo* ItemTableInfo, float Duration);
	void BuffEnd();
	void BuffSlotChange(UBuffSlotWidget* NextBuffSlotWidget);
};
