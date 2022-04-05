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
	UButton* m_StartButton;

	UButton* m_LoadButton;

	UButton* m_QuitButton;

	class ULoadWidget* m_LoadWidget;
	
	protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	public:
	UFUNCTION()
	void StartButton();

	UFUNCTION()
	void LoadButton();
	
	UFUNCTION()
	void QuitButton();

};
