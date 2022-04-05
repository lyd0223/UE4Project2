// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "LootHUDWidget.generated.h"

UCLASS()
class PROJECT1_API ULootHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UListView* m_LootListView;

	class ALootBox* m_LootBox;
	
public:
	UListView* GetLootListView() const
	{
		return m_LootListView;
	}
	void SetLootBox(class ALootBox* LootBox)
	{
		m_LootBox = LootBox;
	}
	
protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
	void ItemClick(UObject* Data);

	UFUNCTION()
	void ItemHovered(UObject* Data, bool Hovered);
};
