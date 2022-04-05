// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Monster.h"
#include "Project1/Monster/BossMonster/BossMonster.h"
#include "Rampage.generated.h"

UCLASS()
class PROJECT1_API ARampage : public ABossMonster
{
	GENERATED_BODY()
	
	public:
	ARampage();

	protected:
	virtual void BeginPlay() override;

	public:
	virtual void Tick(float DeltaTime) override;

	public:
	virtual void NormalAttack() override;
	virtual void UseSkill(int32 Index) override;

	protected:
	void Skill1();
	void Skill2();
	void Skill3();
};
