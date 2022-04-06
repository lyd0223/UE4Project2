// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "StartMainWidget.generated.h"

UCLASS()
class PROJECT1_API UStartMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY()
	UButton* m_SignInButton;

	UPROPERTY()
	UButton* m_SignUpButton;

	UPROPERTY()
	UButton* m_QuitButton;

	UPROPERTY()
	class USignUpWidget* m_SignUpWidget;
	
	protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	public:
	UFUNCTION()
	void SignInButtonClicked();

	UFUNCTION()
	void SignUpButtonClicked();
	
	UFUNCTION()
	void QuitButtonClicked();

};
