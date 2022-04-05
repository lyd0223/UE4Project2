// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	m_Direction = 0.f;
	m_Speed = 0.f;
	m_IsAttack = false;
	m_IsOnGround = true;

	m_AnimType = EPlayerAnimType::Ground;

	//m_FallRecoveryAdditive = 0.f;

	m_Pitch = 0.f;

	m_IsHit = false;
}


void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (player)
	{
		UCharacterMovementComponent* Movement = player->GetCharacterMovement();

		if (Movement)
		{
			// 속도를 구한다.
			m_Speed = Movement->Velocity.Size();

			// 땅을 밟고 있는지 구한다.
			bool OnGround = Movement->IsMovingOnGround();
			
			if(!m_IsOnGround && OnGround && m_AnimType != EPlayerAnimType::Dash)
				m_AnimType = EPlayerAnimType::Ground;
			m_IsOnGround = OnGround;

			// if (!m_IsOnGround && m_AnimType != EPlayerAnimType::Jump)
			// {
			// 	m_AnimType = EPlayerAnimType::Fall;
			// 	//m_FallRecoveryAdditive = 0.f;
			// }
		}
	}
}


void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	m_IsAttack = false;
	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if(player)
		player->AttackEnd();

	
}

void UPlayerAnimInstance::AnimNotify_JumpEnd()
{
	
}


void UPlayerAnimInstance::AnimNotify_DashEnd()
{
	m_AnimType = EPlayerAnimType::Ground;
	
	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if(player)
		player->DashEnd();
}


void UPlayerAnimInstance::AnimNotify_HitEnd()
{
	m_IsHit = false;
}