#pragma once

#include "Project1/GameInfo.h"
#include "Project1/Effect/NormalEffect.h"
#include "AttackEffect.generated.h"

UCLASS()
class PROJECT1_API AAttackEffect : public ANormalEffect
{
	GENERATED_BODY()

public:
	AAttackEffect();

protected:
	UPROPERTY()
	ACharacter* m_OwnerCharacter;

	uint32 m_Damage;

public:
	
	void SetDamage(int32 _Damage)
	{
		m_Damage = _Damage;
	}

	void SetOwnerMonster(class ACharacter* _OwnerCharacter)
	{
		m_OwnerCharacter = _OwnerCharacter;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Init(const FString& _Name, ACharacter* _OwnerCharacter, uint32 _Damage);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ParticleFinish(UParticleSystemComponent* Particle) override;
	virtual void Attack();
};
