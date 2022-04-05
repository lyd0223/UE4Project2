// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "MyItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UMyItem : public UObject
{
	GENERATED_BODY()

public:
	UMyItem();
	UMyItem(const FItemTableInfo* ItemTableInfo);
	virtual ~UMyItem();

protected:
	const FItemTableInfo* m_ItemTableInfo;
	int32 m_Count;

public:
	int32 GetCount() const
	{
		return m_Count;
	}

	void SetCount(int32 Count)
	{
		m_Count = Count;
	}

	void AddItemCount()
	{
		m_Count++;
	}

public:
	void Init(const FItemTableInfo* ItemTableInfo);

public:
	virtual void Use(class APlayerCharacter* Character);

private:
};
