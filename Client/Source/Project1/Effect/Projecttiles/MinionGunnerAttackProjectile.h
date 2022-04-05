// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ParticleProjectile.h"
#include "MinionGunnerAttackProjectile.generated.h"

UCLASS()
class PROJECT1_API AMinionGunnerAttackProjectile : public AParticleProjectile
{
	GENERATED_BODY()
	
	public:
	// Sets default values for this actor's properties
	AMinionGunnerAttackProjectile();

	private:
	int32	m_Attack;

	class AMinionGunner* m_OwnerMonster;
	
	public:
	void SetAttack(int32 Attack)
	{
		m_Attack = Attack;
	}
	void SetOwnerMonster(class AMinionGunner* Monster)
	{
		m_OwnerMonster = Monster;
	}

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	protected:
	virtual void StopEvent(const FHitResult& result);
};
