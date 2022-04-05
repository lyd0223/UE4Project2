// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "ParticleProjectile.h"
#include "GunnerNormalAttackProjectile.generated.h"


UCLASS()
class PROJECT1_API AGunnerNormalAttackProjectile : public AParticleProjectile
{
	GENERATED_BODY()

	public:
	// Sets default values for this actor's properties
	AGunnerNormalAttackProjectile();

	private:
	int32	m_Attack;

	class APlayerCharacter* m_OwnerPlayer;
	
	public:
	void SetAttack(int32 Attack)
	{
		m_Attack = Attack;
	}
	void SetOwnerPlayer(class APlayerCharacter* Player)
	{
		m_OwnerPlayer = Player;
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
