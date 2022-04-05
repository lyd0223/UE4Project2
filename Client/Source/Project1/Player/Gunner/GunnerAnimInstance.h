// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "../PlayerAnimInstance.h"
#include "GunnerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UGunnerAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()

	public:
	UGunnerAnimInstance();

	
	public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	public:
	UFUNCTION()
	void AnimNotify_Fire();

};
