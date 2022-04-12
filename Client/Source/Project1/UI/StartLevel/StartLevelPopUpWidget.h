// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "StartLevelPopUpWidget.generated.h"

UCLASS()
class PROJECT1_API UStartLevelPopUpWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UButton* m_CloseButton;

	UPROPERTY()
	UTextBlock* m_PopUpTextBlock;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void CloseButtonClicked();
	
	UFUNCTION()
	void SetPopUpText(const FString& _Text);
};
