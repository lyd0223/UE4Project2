// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class PROJECT1_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FMonsterInfo	m_MonsterInfo;

	class ASpawnPoint* m_SpawnPoint;

	FString			m_MonsterInfoName;

	class UMonsterAnimInstance* m_AnimInstance;
	
	bool		m_AttackEnd;

	class APlayerCharacter* m_Target;
	
	public:
	class UMonsterAnimInstance* GetAnim()	const
	{
		return m_AnimInstance;
	}
	
	bool GetAttackEnd()	const
	{
		return m_AttackEnd;
	}

	void SetAttackEnd(bool AttackEnd)
	{
		m_AttackEnd = AttackEnd;
	}
	
	void SetSpawnPoint(class ASpawnPoint* SpawnPoint)
	{
		m_SpawnPoint = SpawnPoint;
	}

	FMonsterInfo& GetMonsterInfo()
	{
		return m_MonsterInfo;
	}

	void SetTarget(class APlayerCharacter* Target)
	{
		m_Target = Target;
	}
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	
	public:
	void Death();

	public:
	virtual void NormalAttack();
	
	virtual void UseSkill(int32 Index);
	
};
