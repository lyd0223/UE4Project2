// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ServerConnectInfoWidget.generated.h"

UCLASS()
class PROJECT1_API UServerConnectInfoWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UButton* m_ConnectButton;
	UPROPERTY()
	UButton* m_CloseButton;

	UPROPERTY()
	UEditableTextBox* m_IPTextBox;
	UPROPERTY()
	UEditableTextBox* m_PortTextBox;

	FString m_IPString;
	FString m_PortString;

	UPROPERTY()
	UImage* m_ConnectStatusImage;
	UPROPERTY()
	UTextBlock* m_ConnectStatusText;
	

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void ConnectButtonClicked();
	UFUNCTION()
	void CloseButtonClicked();

	UFUNCTION()
	void IPTextBoxChanged(const FText& Text);
	UFUNCTION()
	void PortTextBoxChanged(const FText& Text);
};
