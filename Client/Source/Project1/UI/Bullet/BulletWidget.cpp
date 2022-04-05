// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletWidget.h"
#include "BulletListItemData.h"

void UBulletWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	m_BulletListView = Cast<UListView>(GetWidgetFromName(TEXT("BulletListView")));
	
	m_BulletListView->OnItemClicked().AddUObject(this, &UBulletWidget::ItemClick);
	m_BulletListView->OnItemIsHoveredChanged().AddUObject(this, &UBulletWidget::ItemHovered);
}

void UBulletWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UBulletWidget::AddBulletListView(class UBulletListItemData* BulletListItemData)
{
	m_BulletListView->AddItem(BulletListItemData);
}


void UBulletWidget::ItemClick(UObject* Data)
{
	//아이템 클릭시 획득하여 인벤토리에 넣어준다.
	
}

void UBulletWidget::ItemHovered(UObject* Data, bool Hovered)
{
	UBulletListItemData* ItemData = Cast<UBulletListItemData>(Data);
	if (ItemData)
	{
		if(Hovered)
			ItemData->GetOwnerBulletWidget()->Hovered();
		else
			ItemData->GetOwnerBulletWidget()->UnHovered();
	}
}
