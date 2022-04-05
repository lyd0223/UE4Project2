// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MyItem.h"
#include "UseItem.generated.h"

UCLASS()
class PROJECT1_API UUseItem : public UMyItem
{
	GENERATED_BODY()

	public:
	virtual ~UUseItem();

	public:
	void Use(APlayerCharacter* Character) override;
};
