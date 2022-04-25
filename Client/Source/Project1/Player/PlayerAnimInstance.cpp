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

void UPlayerAnimInstance::NativeBeginPlay()
{
	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character == nullptr)
		return;
	m_PrevLoc = Character->GetActorLocation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
	
	if (Character)
	{
		UCharacterMovementComponent* Movement = Character->GetCharacterMovement();

		if (Movement)
		{
			//속도계산.
			FVector NowLoc = Character->GetActorLocation();
			FVector Dir = NowLoc - m_PrevLoc;
			m_Speed = abs(Dir.Size()) / DeltaSeconds;
			
				PrintViewport(5.f, FColor::White, FString::Printf(TEXT("%f"), m_Speed));
			
			// 땅을 밟고 있는지 구한다.
			bool OnGround = Movement->IsMovingOnGround();
			
			if(!m_IsOnGround && OnGround && m_AnimType != EPlayerAnimType::Dash)
				m_AnimType = EPlayerAnimType::Ground;
			m_IsOnGround = OnGround;
		}
		
		m_PrevLoc = Character->GetActorLocation();
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