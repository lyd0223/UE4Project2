// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"

#include "Monster.h"


UMonsterAnimInstance::UMonsterAnimInstance()
{
	m_OnGround = true;

	m_AnimType = EMonsterAnimType::Idle;

}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster)
	{
		UCharacterMovementComponent* Movement = Monster->GetCharacterMovement();

		if (Movement)
		{
			bool OnGround = Movement->IsMovingOnGround();

			m_OnGround = OnGround;
		}
	}
}


void UMonsterAnimInstance::AnimNotify_SpawnEnd()
{
	m_AnimType = EMonsterAnimType::Idle;
}

void UMonsterAnimInstance::AnimNotify_Attack()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster)
		Monster->NormalAttack();
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	//PrintViewport(1.f, FColor::Red, TEXT("AttackEnd"));
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster)
		Monster->SetAttackEnd(true);
}


void UMonsterAnimInstance::AnimNotify_Death()
{
	AMonster* Monster = Cast<AMonster>(TryGetPawnOwner());

	if (Monster)
		Monster->Death();
}