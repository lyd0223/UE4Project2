// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItem.h"


UMyItem::UMyItem()
{
	m_ItemTableInfo = nullptr;
	m_Count = 0;
}

UMyItem::~UMyItem()
{
	delete(m_ItemTableInfo);
	
}

UMyItem::UMyItem(const FItemTableInfo* ItemTableInfo)
{
	m_ItemTableInfo = ItemTableInfo;
}

void UMyItem::Init(const FItemTableInfo* ItemTableInfo)
{
	m_ItemTableInfo = ItemTableInfo;
}

void UMyItem::Use(APlayerCharacter* Character)
{
	
}
