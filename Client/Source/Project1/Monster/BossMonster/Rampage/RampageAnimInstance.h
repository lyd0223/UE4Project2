// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../MonsterAnimInstance.h"
#include "RampageAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API URampageAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()


	public:
	UFUNCTION()
	void AnimNotify_Skill2Attack();
	UFUNCTION()
	void AnimNotify_AttachEnd();
	
};
