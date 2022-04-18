// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Project1/Global/Message/ContentsStruct.h"
#include "CharacterDescWidget.generated.h"

UCLASS()
class PROJECT1_API UCharacterDescWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_DescText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* m_BackgroundImage1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* m_BackgroundImage2;
	
	TMap<EPlayerJob, FSelectPlayerTableInfo> m_SelectPlayerTableInfoMap;
	class USelectCharacterMainWidget* m_OwnerWidget;

public:
	void SetOwnerWidget(class USelectCharacterMainWidget* _OwnerWidget)
	{
		m_OwnerWidget = _OwnerWidget;
	}

protected:
	virtual void NativeConstruct() override;

public:
	void SetDesc(EPlayerJob PlayerJob);
	void SetDesc(EPlayerJob PlayerJob, const TMap<EPlayerJob, FCharacterInfo>& _CharacterInfoMap);
};
