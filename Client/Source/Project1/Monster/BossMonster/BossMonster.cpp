// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonster.h"

ABossMonster::ABossMonster()
{
	m_IsSkillOn = true;
}

// Called when the game starts or when spawned
void ABossMonster::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &ABossMonster::IsSkillOnSetTrue, 5.f, false);
}

// Called every frame
void ABossMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABossMonster::NormalAttack()
{
	Super::NormalAttack();
}


void ABossMonster::UseSkill(int32 Index)
{
	Super::UseSkill(Index);

}

void ABossMonster::IsSkillOnSetTrue()
{
	m_IsSkillOn = true;
	
	GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &ABossMonster::IsSkillOnSetTrue, 5.f, false);
}