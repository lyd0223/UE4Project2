// Fill out your copyright notice in the Description page of Project Settings.


#include "GunnerNormalAttackProjectile.h"
#include "../NormalEffect.h"
#include "../../Player/PlayerCharacter.h"

AGunnerNormalAttackProjectile::AGunnerNormalAttackProjectile()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem>	ParticleAsset(TEXT("ParticleSystem'/Game/ParagonRevenant/FX/Particles/Revenant/Abilities/Mark/FX/P_Revenant_Mark_Trail.P_Revenant_Mark_Trail'"));

	if (ParticleAsset.Succeeded())
		m_Particle->SetTemplate(ParticleAsset.Object);
	
	m_Movement->InitialSpeed = 2000.f;

	m_Body->SetCollisionProfileName("PlayerAttackObj");
}

void AGunnerNormalAttackProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void AGunnerNormalAttackProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGunnerNormalAttackProjectile::StopEvent(const FHitResult& result)
{
	Super::StopEvent(result);

	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
		result.ImpactPoint, result.Normal.Rotation(), param);
	
	Effect->LoadParticleAsync(TEXT("GunnerNormalAttackHit"));
	Effect->SetEffectScale(FVector(0.5f,0.5f,0.5f));
	//Effect->LoadSoundAsync(TEXT("GunnerNormalAttackHit"));

	//데미지 처리
	FDamageEvent	DmgEvent;
	float Damage = result.GetActor()->TakeDamage(m_OwnerPlayer->GetPlayerInfo().ATK, DmgEvent, m_OwnerPlayer->GetController(), this);

	Destroy();
}
