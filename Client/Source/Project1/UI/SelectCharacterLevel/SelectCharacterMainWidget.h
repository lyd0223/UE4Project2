// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "SelectCharacterMainWidget.generated.h"

UCLASS()
class PROJECT1_API USelectCharacterMainWidget : public UUserWidget
{
	GENERATED_BODY()

	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_Character1Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_Character2Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_Character3Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_Character4Button;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_CreateButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCharacterStatGraphWidget* m_CharacterStatGraphWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCharacterDescWidget* m_CharacterDescWidget;

	EPlayerJob m_SelectJob;
	class UCanvasPanelSlot* m_SelectPanelSlot;
	
	protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	public:
	
	UFUNCTION()
	void Character1ButtonClick();
	UFUNCTION()
	void Character2ButtonClick();
	UFUNCTION()
	void Character3ButtonClick();
	UFUNCTION()
	void Character4ButtonClick();
	
	UFUNCTION()
	void CreateButtonClick();
	UFUNCTION()
	void BackButtonClick();

	public:
	void SetKnightStateVisibility(ESlateVisibility Visible);
	void SetArcherStateVisibility(ESlateVisibility Visible);
	void SetInputNameVisibility(ESlateVisibility Visible);
	void SetKnightInfo(const FPlayerInfo& Info);
	void SetArcherInfo(const FPlayerInfo& Info);
};
