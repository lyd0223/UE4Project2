// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Ground,
	Jump,
	Dash,
	Death
};

UCLASS()
class PROJECT1_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	public:
	UPlayerAnimInstance();
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_IsAttack;
	bool	m_IsOnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_IsHit;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerAnimType	m_AnimType;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// float	m_FallRecoveryAdditive;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_Pitch;
	
	public:
	float GetDirection()
	{
		return m_Direction;
	}

	void SetDirection(float Direction)
	{
		m_Direction = Direction;
	}

	void SetAttackEnable(bool Attack)
	{
		m_IsAttack = Attack;
	}

	float GetPitch()
	{
		return m_Pitch;
	}
	void SetPitch(float Pitch)
	{
		m_Pitch = Pitch;
	}
	
	bool GetIsAttack()	const
	{
		return m_IsAttack;
	}

	void ChangeAnimType(EPlayerAnimType Type)
	{
		m_AnimType = Type;
	}

	EPlayerAnimType GetAnimType()
	{
		return m_AnimType;
	}

	void SetHit(bool IsHit)
	{
		m_IsHit = IsHit;
	}

	public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	public:
	UFUNCTION()
	void AnimNotify_AttackEnd();
	UFUNCTION()
	void AnimNotify_JumpEnd();
	UFUNCTION()
	void AnimNotify_DashEnd();
	UFUNCTION()
	void AnimNotify_HitEnd();

};
