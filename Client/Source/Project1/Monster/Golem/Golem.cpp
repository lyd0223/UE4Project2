// Fill out your copyright notice in the Description page of Project Settings.


#include "Golem.h"
#include "GolemAIController.h"
#include "Project1/Effect/NormalEffect.h"

AGolem::AGolem()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Prime_Helix/Meshes/Prime_Helix.Prime_Helix'"));
	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("AnimBlueprint'/Game/01Resources/Monster/Golem/BPGolemAnim.BPGolemAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	m_MonsterInfoName = TEXT("Golem");
	
	AIControllerClass = AGolemAIController::StaticClass();

}

// Called when the game starts or when spawned
void AGolem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGolem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGolem::NormalAttack()
{
	FVector	Loc = GetActorLocation();
	FVector	Forward = GetActorForwardVector();

	FCollisionQueryParams	params(NAME_None, false, this);
	
	FHitResult	result;
	bool Sweep = GetWorld()->SweepSingleByChannel(result, Loc,
		Loc + Forward * m_MonsterInfo.AttackDistance, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4, 
		FCollisionShape::MakeBox(FVector(60.f,60.f,60.f)),
		params);

	//디버그용 캡슐드로우
#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = Sweep ? FColor::Red : FColor::Green;

	FVector Center = Loc + Forward * m_MonsterInfo.AttackDistance / 2.f;

	DrawDebugBox(GetWorld(), Center,FVector(60.f,60.f,60.f),
		DrawColor, false, 0.5f);

#endif

	if (Sweep)
	{
		//이펙트
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
			result.ImpactPoint, result.ImpactNormal.Rotation(), param);
		
		Effect->LoadParticleAsync(TEXT("GolemHit"));
		
		// // Sound
		// Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));


		//공격 데미지
		FDamageEvent	DmgEvent;
		float Damage = result.GetActor()->TakeDamage(m_MonsterInfo.Attack, DmgEvent, GetController(), this);
	}
}