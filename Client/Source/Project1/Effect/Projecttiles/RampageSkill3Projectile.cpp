#include "RampageSkill3Projectile.h"
#include "Project1/Effect/NormalEffect.h"
#include "Project1/Monster/MinionGunner/MinionGunner.h"


ARampageSkill3Projectile::ARampageSkill3Projectile()
{
	m_Body->SetBoxExtent(FVector(50.f,50.f,50.f));
	
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>	MeshAsset(TEXT("StaticMesh'/Game/ParagonRampage/FX/Meshes/Debris/SM_Rock_02.SM_Rock_02'"));
	if (MeshAsset.Succeeded())
		m_Mesh->SetStaticMesh(MeshAsset.Object);
	m_Mesh->SetupAttachment(m_Body);
	
	// static ConstructorHelpers::FObjectFinder<UParticleSystem>	ParticleAsset(TEXT("ParticleSystem'/Game/ParagonMinions/FX/Particles/Buffs/Buff_Blue/FX/P_Spit_Attack_Projectile.P_Spit_Attack_Projectile'"));
	// if (ParticleAsset.Succeeded())
	// 	m_Particle->SetTemplate(ParticleAsset.Object);
	
	m_Movement->InitialSpeed = 2000.f;
	m_Movement->ProjectileGravityScale = 10.f;
	
	m_Body->SetCollisionProfileName("EnemyAttackObj");
	m_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARampageSkill3Projectile::BeginPlay()
{
	Super::BeginPlay();

}

void ARampageSkill3Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//PrintViewport(0.5f, FColor::Blue, "Tick");
}

void ARampageSkill3Projectile::StopEvent(const FHitResult& result)
{
	Super::StopEvent(result);

	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
		result.ImpactPoint, result.Normal.Rotation(), param);
	
	Effect->LoadParticleAsync(TEXT("RampageSkill3"));
	//Effect->LoadSoundAsync(TEXT("GunnerNormalAttackHit"));

	//데미지 처리
	FDamageEvent	DmgEvent;
	float Damage = result.GetActor()->TakeDamage(m_OwnerMonster->GetMonsterInfo().Attack, DmgEvent, m_OwnerMonster->GetController(), this);

	Destroy();
}
