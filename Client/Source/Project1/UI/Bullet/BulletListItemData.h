// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "BulletListItemData.generated.h"

UCLASS()
class PROJECT1_API UBulletListItemData : public UObject
{
	GENERATED_BODY()
	
	public:
	UBulletListItemData();

	protected:
	FBullet* m_Bullet;

	UPROPERTY()
	class UBulletListItemWidget* m_OwnerBulletWidget;
	
	public:
	void SetBullet(FBullet* Bullet)
	{
		m_Bullet = Bullet;
	}

	FBullet* GetBullet() const
	{
		return m_Bullet;
	}

	void SetOwnerBulletWidget(class UBulletListItemWidget* BulletWidget)
	{
		m_OwnerBulletWidget = BulletWidget;
	}
	UBulletListItemWidget* GetOwnerBulletWidget() const
	{
		return m_OwnerBulletWidget;
	}
};
