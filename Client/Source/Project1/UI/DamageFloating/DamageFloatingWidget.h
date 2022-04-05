// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DamageFloatingWidget.generated.h"

UCLASS()
class PROJECT1_API UDamageFloatingWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_DamageText;

	AActor* m_OwnerActor;
	
	float m_Opacity;
	
	public :
	void SetDamageText(int32 Damage)
	{
		m_Opacity = 1.f;
		m_DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageText")));
		m_DamageText->SetText(FText::FromString(FString::FromInt(Damage)));
	}
	void SetOwnerActor(AActor* OwnerActor)
	{
		m_OwnerActor = OwnerActor;
	}
	
	protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
};
