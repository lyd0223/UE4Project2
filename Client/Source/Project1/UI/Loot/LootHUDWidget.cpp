// Fill out your copyright notice in the Description page of Project Settings.


#include "LootHUDWidget.h"

#include "LootListItemData.h"
#include "LootListItemWidget.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Effect/NormalEffect.h"
#include "Project1/Manager/InventoryManager.h"
#include "Project1/Map/LootBox.h"

void ULootHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_LootListView = Cast<UListView>(GetWidgetFromName(TEXT("LootListView")));

	m_LootListView->OnItemClicked().AddUObject(this, &ULootHUDWidget::ItemClick);
	m_LootListView->OnItemIsHoveredChanged().AddUObject(this, &ULootHUDWidget::ItemHovered);

	m_LootBox = nullptr;
}

void ULootHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void ULootHUDWidget::ItemClick(UObject* Data)
{
	//아이템 클릭시 획득하여 인벤토리에 넣어준다.
	ULootListItemData* ItemData = Cast<ULootListItemData>(Data);
	if (ItemData)
	{
		UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(m_LootBox->GetWorld()->GetGameInstance());
		if(IsValid(GameInstance))
		{
			m_LootListView->RemoveItem(Data);
			GameInstance->GetInventoryManager()->AddItem(ItemData->GetItem());
			
			FVector Loc = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), Loc,
				FRotator::ZeroRotator, param);
			Effect->LoadSoundAsync(TEXT("PickUp"));
			Effect->SetLifeTime(1.f);
			
			m_LootBox->GetDropItemArray().Remove(ItemData->GetItem());
		}
		
	}
}

void ULootHUDWidget::ItemHovered(UObject* Data, bool Hovered)
{
	ULootListItemData* ItemData = Cast<ULootListItemData>(Data);
	if (ItemData)
	{
		if(Hovered)
			ItemData->GetOwnerItemWidget()->Hovered();
		else
			ItemData->GetOwnerItemWidget()->UnHovered();
	}
}
