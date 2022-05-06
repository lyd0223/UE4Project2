#pragma once
#include "../../GameInfo.h"
#include "ParticleProjectile.h"
#include "RampageSkill1Projectile.generated.h"


UCLASS()
class PROJECT1_API ARampageSkill1Projectile : public AParticleProjectile
{
	GENERATED_BODY()

	public:
	// Sets default values for this actor's properties
	ARampageSkill1Projectile();

	private:
	int32	m_Damage;

	class AMonster* m_OwnerMonster;;
	
	public:
	void SetDamage(int32 _Damage)
	{
		m_Damage = _Damage;
	}
	void SetOwnerMonster(class AMonster* _OwnerMonster)
	{
		m_OwnerMonster = _OwnerMonster;
	}

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	protected:
	virtual void StopEvent(const FHitResult& result) override;
};
