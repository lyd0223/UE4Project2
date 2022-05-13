#include "AttackEffect.h"


AAttackEffect::AAttackEffect()
{
	m_OwnerCharacter = nullptr;
}


void AAttackEffect::BeginPlay()
{
	Super::BeginPlay();
}

void AAttackEffect::Init(const FString& _Name, ACharacter* _OwnerCharacter, uint32 _Damage)
{
	LoadParticleAsync(_Name);
	LoadSoundAsync(_Name);

	m_OwnerCharacter = _OwnerCharacter;
	m_Damage = _Damage;
}

void AAttackEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAttackEffect::ParticleFinish(UParticleSystemComponent* Particle)
{
	Attack();
	this->Destroy();
}

void AAttackEffect::Attack()
{
	
}