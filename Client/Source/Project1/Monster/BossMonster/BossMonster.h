// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Monster.h"
#include "BossMonster.generated.h"

UCLASS()
class PROJECT1_API ABossMonster : public AMonster
{
	GENERATED_BODY()

public:
	ABossMonster();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> m_SkillMontageArray;

	FTimerHandle m_TimerHandle;

	bool m_IsSkillOn;

public:
	bool GetIsSkillOn() const
	{
		return m_IsSkillOn;
	}

	void SetIsSkillOn(bool SkillOn)
	{
		m_IsSkillOn = SkillOn;
	}

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void NormalAttack() override;
	virtual void UseSkill(int32 Index) override;

protected:
	void IsSkillOnSetTrue();
};
