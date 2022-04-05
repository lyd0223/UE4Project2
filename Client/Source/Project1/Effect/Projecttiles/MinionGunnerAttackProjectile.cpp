// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionGunnerAttackProjectile.h"

#include "Project1/Effect/NormalEffect.h"
#include "Project1/Monster/MinionGunner/MinionGunner.h"


AMinionGunnerAttackProjectile::AMinionGunnerAttackProjectile()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem>	ParticleAsset(TEXT("ParticleSystem'/Game/ParagonMinions/FX/Particles/Buffs/Buff_Blue/FX/P_Spit_Attack_Projectile.P_Spit_Attack_Projectile'"));

	if (ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);
	
	m_Movement->InitialSpeed = 1000.f;

	m_Body->SetCollisionProfileName("EnemyAttackObj");
}

void AMinionGunnerAttackProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void AMinionGunnerAttackProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//PrintViewport(0.5f, FColor::Blue, "Tick");
}

void AMinionGunnerAttackProjectile::StopEvent(const FHitResult& result)
{
	Super::StopEvent(result);

	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
		result.ImpactPoint, result.Normal.Rotation(), param);
	
	Effect->LoadParticleAsync(TEXT("MinionGunnerHit"));
	//Effect->SetEffectScale(FVector(0.5f,0.5f,0.5f));
	//Effect->LoadSoundAsync(TEXT("GunnerNormalAttackHit"));

	//데미지 처리
	FDamageEvent	DmgEvent;
	float Damage = result.GetActor()->TakeDamage(m_OwnerMonster->GetMonsterInfo().Attack, DmgEvent, m_OwnerMonster->GetController(), this);

	Destroy();
}
