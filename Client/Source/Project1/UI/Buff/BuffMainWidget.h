// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "BuffMainWidget.generated.h"

UCLASS()
class PROJECT1_API UBuffMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class UBuffSlotWidget*> m_BuffSlotWidgetArray;

	class APlayerCharacter* m_PlayerCharacter;
	
	public:
	class APlayerCharacter* GetPlayerCharacter() const
	{
		return m_PlayerCharacter;
	}
	void SetPlayerCharacter(class APlayerCharacter* PlayerCharacter)
	{
		m_PlayerCharacter = PlayerCharacter;
	}

	protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	public:
	void AddBuff(const FItemTableInfo* ItemTableInfo, float Duration);
	void BuffRefresh(uint8 StartIndex);
};
