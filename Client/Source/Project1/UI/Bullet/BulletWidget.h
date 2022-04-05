// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "BulletWidget.generated.h"

UCLASS()
class PROJECT1_API UBulletWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UListView* m_BulletListView;

public :
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void AddBulletListView(class UBulletListItemData* BulletListItemData);
	
	UFUNCTION()
	void ItemClick(UObject* Data);

	UFUNCTION()
	void ItemHovered(UObject* Data, bool Hovered);
};
