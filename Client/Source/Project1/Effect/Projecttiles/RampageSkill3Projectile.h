#pragma once

#include "ParticleProjectile.h"
#include "RampageSkill3Projectile.generated.h"

UCLASS()
class PROJECT1_API ARampageSkill3Projectile : public AParticleProjectile
{
	GENERATED_BODY()
	
	public:
	// Sets default values for this actor's properties
	ARampageSkill3Projectile();

	private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_Mesh;
	
	int32	m_Attack;

	class AMonster* m_OwnerMonster;
	
	public:
	void SetAttack(int32 Attack)
	{
		m_Attack = Attack;
	}
	void SetOwnerMonster(class AMonster* Monster)
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
