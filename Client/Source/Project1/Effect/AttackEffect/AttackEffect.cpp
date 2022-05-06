#include "AttackEffect.h"


AAttackEffect::AAttackEffect()
{
	m_Body = CreateDefaultSubobject<USphereComponent>(TEXT("Body"));
	SetRootComponent(m_Body);

	m_Body->SetCollisionProfileName(TEXT("EnemyAttackObj"));
	m_OwnerMonster = nullptr;
}


void AAttackEffect::BeginPlay()
{
	
}

void AAttackEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AAttackEffect::Attack()
{
	
}