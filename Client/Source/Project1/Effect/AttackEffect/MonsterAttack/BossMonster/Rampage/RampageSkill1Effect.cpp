#include "RampageSkill1Effect.h"

ARampageSkill1Effect::ARampageSkill1Effect()
{
	PrimaryActorTick.bCanEverTick = true;
	
	m_Body->SetSphereRadius(100.f);

	m_Damage = 0.f;
}

void ARampageSkill1Effect::BeginPlay()
{
	Super::BeginPlay();

}

void ARampageSkill1Effect::Tick(float DeltaTime)
{
	
	
}

void ARampageSkill1Effect::Attack()
{
	//충돌 Effect 
	// FActorSpawnParameters	param;
	// param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//
	// ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
	// 	result.ImpactPoint, result.Normal.Rotation(), param);
	//
	// Effect->LoadParticleAsync(TEXT("MinionGunnerHit"));
	// Effect->SetEffectScale(FVector(0.5f,0.5f,0.5f));
	// Effect->LoadSoundAsync(TEXT("GunnerNormalAttackHit"));

	//데미지 처리
	FDamageEvent	DmgEvent;
	float Damage = result.GetActor()->TakeDamage(m_OwnerMonster->GetMonsterInfo().Attack, DmgEvent, m_OwnerMonster->GetController(), this);

	Destroy();
}