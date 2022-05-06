#pragma once

#include "../../GameInfo.h"
#include "Project1/Effect/NormalEffect.h"
#include "ParticleProjectile.generated.h"

UCLASS()
class PROJECT1_API AAttackEffect : public ANormalEffect
{
	GENERATED_BODY()

public:
	AAttackEffect();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USphereComponent* m_Body;

	UPROPERTY()
	class AMonster* m_OwnerMonster;;

	int m_Damage;

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

	virtual void Attack();
};
