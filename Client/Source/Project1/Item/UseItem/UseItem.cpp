// Fill out your copyright notice in the Description page of Project Settings.


#include "UseItem.h"


UUseItem::~UUseItem()
{
	delete(m_ItemTableInfo);
	
}

void UUseItem::Use(APlayerCharacter* Character)
{
	Super::Use(Character);
}

