#include "RampageSkill1Effect.h"

ARampageSkill1Effect::ARampageSkill1Effect()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Damage = 0.f;
}

void ARampageSkill1Effect::BeginPlay()
{
	Super::BeginPlay();

}

void ARampageSkill1Effect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ARampageSkill1Effect::Attack()
{
	Super::Attack();
	
	FCollisionQueryParams	params(NAME_None, false, this);
	float Radious = 300.f;
	FVector Loc = GetActorLocation();
	FHitResult	result;
	bool Sweep = GetWorld()->SweepSingleByChannel(result, Loc,
		Loc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4, 
		FCollisionShape::MakeSphere(Radious),
		params);
	
	if(Sweep)
	{
		//충돌 Effect 
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
																result.ImpactPoint, result.Normal.Rotation(), param);
		Effect->LoadParticleAsync(TEXT("MinionGunnerHit"));
		Effect->SetEffectScale(FVector(0.5f, 0.5f, 0.5f));
		Effect->LoadSoundAsync(TEXT("GunnerNormalAttackHit"));
		//데미지 처리
		FDamageEvent DmgEvent;
		float Damage = result.GetActor()->TakeDamage(m_Damage, DmgEvent,
													m_OwnerCharacter->GetController(), this);
	}

}