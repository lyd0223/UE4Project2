// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EMonsterAnimType : uint8
{
	Spawn,
	Idle,
	Walk,
	Run,
	Attack,
	Skill,
	Death,
	None
};

UCLASS()
class PROJECT1_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	public:
	UMonsterAnimInstance();
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_OnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EMonsterAnimType	m_AnimType;

	
	public:
	EMonsterAnimType GetAnimType()	const
	{
		return m_AnimType;
	}

	void ChangeAnimType(EMonsterAnimType Type)
	{
		m_AnimType = Type;
	}

	public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	public:
	UFUNCTION()
	void AnimNotify_SpawnEnd();

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_Death();
	
};
