// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonster.h"

#include "Project1/Project1GameModeBase.h"
#include "Project1/Player/PlayerCharacter.h"

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

void ABossMonster::Death()
{
	Super::Death();

	AProject1GameModeBase* GameMode = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode == nullptr)
		return;
	GameMode->GameClear();
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
	
	GetWorld()->GetTimerManager().SetTimer(m_TimerHandle, this, &ABossMonster::IsSkillOnSetTrue, 3.f, false);
}