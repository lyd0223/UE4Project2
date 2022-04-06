// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "SignUpWidget.generated.h"
/**
 * 
 */
UCLASS()
class PROJECT1_API USignUpWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UButton* m_SignUpButton;
	UPROPERTY()
	UButton* m_CloseButton;
	
	UPROPERTY()
	UEditableTextBox* m_IDTextBox;
	UPROPERTY()
	UEditableTextBox* m_PWTextBox;

	FString m_IDString;
	FString m_PWString;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void SignUpButtonClicked();
	UFUNCTION()
	void CloseButtonClicked();
	
	UFUNCTION()
	void IDTextBoxChanged(const FText& Text);
	UFUNCTION()
	void PWTextBoxChanged(const FText& Text);
};
