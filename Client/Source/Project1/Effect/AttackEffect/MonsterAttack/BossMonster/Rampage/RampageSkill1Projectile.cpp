#include "RampageSkill1Projectile.h"

#include "Project1/Effect/NormalEffect.h"
#include "Project1/Monster/MinionGunner/MinionGunner.h"

ARampageSkill1Projectile::ARampageSkill1Projectile()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem>	ParticleAsset(TEXT("ParticleSystem'/Game/ParagonRampage/FX/Particles/Rampage_v001_IceBlue/FX/P_Rampage_Ice_Enrage_Cast.P_Rampage_Ice_Enrage_Cast'"));

	if (ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);
	
	m_Movement->InitialSpeed = 1000.f;

	m_Body->SetCollisionProfileName("EnemyAttackObj");
}

void ARampageSkill1Projectile::BeginPlay()
{
	Super::BeginPlay();

}

void ARampageSkill1Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ARampageSkill1Projectile::StopEvent(const FHitResult& result)
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