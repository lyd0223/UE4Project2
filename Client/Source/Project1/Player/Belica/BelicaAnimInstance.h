// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerAnimInstance.h"
#include "BelicaAnimInstance.generated.h"

UCLASS()
class PROJECT1_API UBelicaAnimInstance : public UPlayerAnimInstance
{
	GENERATED_BODY()
	
	public:
	UBelicaAnimInstance();

	
	public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	public:
	UFUNCTION()
	void AnimNotify_NormalBullet();
	UFUNCTION()
	void AnimNotify_TrippleBullet();
	UFUNCTION()
	void AnimNotify_RecoveryBullet();
	UFUNCTION()
	void AnimNotify_PowerBullet();
};
