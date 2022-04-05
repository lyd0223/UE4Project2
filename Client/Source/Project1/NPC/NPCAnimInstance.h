// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "NPCAnimInstance.generated.h"

UCLASS()
class PROJECT1_API UNPCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UNPCAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_IsPose;

public:
	void SetIsPose(bool IsPose)
	{
		m_IsPose = IsPose;
	}

public:
	UFUNCTION()
	void AnimNotify_PoseEnd()
	{
		m_IsPose = false;
	}
};
