// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreListItemWidget.h"

#include "StoreListItemData.h"


void UStoreListItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_ItemImage =Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_CountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CountText")));
	m_GoldText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GoldText")));
}

void UStoreListItemWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UStoreListItemWidget::NativeOnListItemObjectSet(
	UObject* ListItemObject)
{
	UStoreListItemData* ListItem = Cast<UStoreListItemData>(ListItemObject);

	// ListItem->SetOwnerBulletWidget(this);
	//
	// FBullet* Bullet = ListItem->GetBullet();
	//
	// m_BulletImage->SetBrushFromTexture(Bullet->BulletTableInfo->IconTexture);
	// m_NameText->SetText(FText::FromString(Bullet->BulletTableInfo->Name));
	// FString Str = Bullet->BulletTableInfo->Desc;
	// FString Str1 = "";
	// FString Str2 = "";
	// for (int i = 0; i < Str.Len(); i++)
	// {
	// 	if (Str[i] == '^')
	// 	{
	// 		Str1.Append(*Str, i);
	// 		Str.RemoveAt(0,i+1);
	// 		Str2.Append(*Str, Str.Len());
	// 	}
	// }
	// m_DescText1->SetText(FText::FromString(Str1));
	// m_DescText2->SetText(FText::FromString(Str2));
	// m_ATKPercentText->SetText(FText::FromString(FString::Printf(TEXT("%d%%"),Bullet->BulletTableInfo->ATKPercent)));
	// m_SPCostText->SetText(FText::FromString(FString::FromInt(Bullet->BulletTableInfo->SPCost)));
	// FLinearColor Color;
	// switch (Bullet->BulletTableInfo->BulletType)
	// {
	// case EBulletType::Recovery:
	// 	Color = FLinearColor(0.f,1.f,0.f,1.f);
	// 	break;
	// case EBulletType::Attack:
	// 	Color = FLinearColor(1.f,0.f,0.f,1.f);
	// 	break;
	// }
	// m_ATKPercentText->SetColorAndOpacity(Color);
}

