// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"

#include "Project1/AssetManager/AssetPathLoader.h"


void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_CharacterImage = Cast<UImage>(GetWidgetFromName(TEXT("CharacterImage")));
	m_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	m_SPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("SPBar")));
	m_EXPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("EXPBar")));

	m_HPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPText")));
	m_SPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SPText")));
	m_LevelText = Cast<UTextBlock>(GetWidgetFromName(TEXT("LevelText")));
	m_EXPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("EXPText")));
}

void UPlayerHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UPlayerHUDWidget::SetCharacterImage(UTexture2D* Texture)
{
	UMaterialInstance* MaterialInst = LoadObject<UMaterialInstance>(nullptr, TEXT("MaterialInstanceConstant'/Game/01Resources/Materials/MTCharacterImage_Inst.MTCharacterImage_Inst'"));
	UMaterialInstanceDynamic* DynamicMaterialInst = UMaterialInstanceDynamic::Create(MaterialInst, nullptr);
	DynamicMaterialInst->SetTextureParameterValue(TEXT("Texture"), Texture);

	m_CharacterImage->SetBrushFromMaterial(DynamicMaterialInst);
}