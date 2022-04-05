// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CharacterStatGraphWidget.generated.h"

UCLASS()
class PROJECT1_API UCharacterStatGraphWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* m_StatGraphImage;

	TMap<EPlayerJob, FSelectPlayerTableInfo> m_SelectPlayerTableInfoMap;
	protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);


	public:
	void SetStatGraphImage(EPlayerJob PlayerJob);
};
