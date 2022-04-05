// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletListItemWidget.h"

#include "BulletListItemData.h"


void UBulletListItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_BorderImage =Cast<UImage>(GetWidgetFromName(TEXT("BorderImage")));
	m_BulletImage = Cast<UImage>(GetWidgetFromName(TEXT("BulletImage")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_DescText1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("DescText1")));
	m_DescText2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("DescText2")));
	m_ATKPercentText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ATKPercentText")));
	m_SPCostText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SPCostText")));
}

void UBulletListItemWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBulletListItemWidget::NativeOnListItemObjectSet(
	UObject* ListItemObject)
{
	UBulletListItemData* ListItem = Cast<UBulletListItemData>(ListItemObject);

	ListItem->SetOwnerBulletWidget(this);

	FBullet* Bullet = ListItem->GetBullet();

	m_BulletImage->SetBrushFromTexture(Bullet->BulletTableInfo->IconTexture);
	m_NameText->SetText(FText::FromString(Bullet->BulletTableInfo->Name));
	FString Str = Bullet->BulletTableInfo->Desc;
	FString Str1 = "";
	FString Str2 = "";
	for (int i = 0; i < Str.Len(); i++)
	{
		if (Str[i] == '^')
		{
			Str1.Append(*Str, i);
			Str.RemoveAt(0,i+1);
			Str2.Append(*Str, Str.Len());
		}
	}
	m_DescText1->SetText(FText::FromString(Str1));
	m_DescText2->SetText(FText::FromString(Str2));
	m_ATKPercentText->SetText(FText::FromString(FString::Printf(TEXT("%d%%"),Bullet->BulletTableInfo->ATKPercent)));
	m_SPCostText->SetText(FText::FromString(FString::FromInt(Bullet->BulletTableInfo->SPCost)));
	FLinearColor Color;
	switch (Bullet->BulletTableInfo->BulletType)
	{
	case EBulletType::Recovery:
		Color = FLinearColor(0.f,1.f,0.f,1.f);
		break;
	case EBulletType::Attack:
		Color = FLinearColor(1.f,0.f,0.f,1.f);
		break;
	}
	m_ATKPercentText->SetColorAndOpacity(Color);
}


void UBulletListItemWidget::Hovered()
{
	m_BorderImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UBulletListItemWidget::UnHovered()
{
	m_BorderImage->SetVisibility(ESlateVisibility::Collapsed);
}