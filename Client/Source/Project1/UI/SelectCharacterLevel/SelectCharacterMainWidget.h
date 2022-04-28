// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Project1/Global/Message/ContentsStruct.h"
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
	UButton* m_DeleteButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_EnterButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCharacterStatGraphWidget* m_CharacterStatGraphWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCharacterDescWidget* m_CharacterDescWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCharacterNameSettingWidget* m_CharacterNameSettingWidget;

	EPlayerJob m_SelectJob;
	class UCanvasPanelSlot* m_SelectPanelSlot;

	std::vector<FCharacterInfo> m_CharacterInfoList;
	TMap<EPlayerJob, FCharacterInfo> m_CharacterInfoMap;

	bool m_IsCanEnter;

public:
	EPlayerJob GetSelectJob() const
	{
		return m_SelectJob;
	}

protected:
	virtual void NativeConstruct() override;

public:
	//DB에서 받아온 정보를 바탕으로 UI 초기화.
	bool UIInitialize(const std::vector<FCharacterInfo>& CharacterInfoList);

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
	void DeleteButtonClick();
	UFUNCTION()
	void EnterButtonClick();
	UFUNCTION()
	void BackButtonClick();

	void EnterButtonOn(bool _IsOn);
	void CharacterStatGraphOn(bool _IsOn);
};
