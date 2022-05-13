// Fill out your copyright notice in the Description page of Project Settings.


#include "Rampage.h"
#include "RampageAIController.h"
#include "RampageAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Project1/Effect/NormalEffect.h"
#include "Project1/Effect/AttackEffect/MonsterAttack/BossMonster/Rampage/RampageSkill1Effect.h"
#include "Project1/Effect/Projecttiles/RampageSkill3Projectile.h"
#include "Project1/Player/PlayerCharacter.h"

ARampage::ARampage()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<AActor>	Skill3RockAsset(TEXT("Blueprint'/Game/01Resources/Monster/BossMonster/Rampage/BP_Skill3Rock.BP_Skill3Rock_C'"));
	if (Skill3RockAsset.Succeeded())
		m_Skill3RockClass = Skill3RockAsset.Class;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("SkeletalMesh'/Game/ParagonRampage/Characters/Heroes/Rampage/Meshes/Rampage.Rampage'"));
	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("AnimBlueprint'/Game/01Resources/Monster/BossMonster/Rampage/BPRampageAnim.BPRampageAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	//Skill Asset Load
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill1Asset(TEXT("AnimMontage'/Game/01Resources/Monster/BossMonster/Rampage/AMRampageSkill1.AMRampageSkill1'"));
	if (Skill1Asset.Succeeded())
		m_SkillMontageArray.Add(Skill1Asset.Object);
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill2Asset(TEXT("AnimMontage'/Game/01Resources/Monster/BossMonster/Rampage/AMRampageSkill2.AMRampageSkill2'"));
	if (Skill2Asset.Succeeded())
		m_SkillMontageArray.Add(Skill2Asset.Object);
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill3Asset(TEXT("AnimMontage'/Game/01Resources/Monster/BossMonster/Rampage/AMRampageSkill3.AMRampageSkill3'"));
	if (Skill3Asset.Succeeded())
		m_SkillMontageArray.Add(Skill3Asset.Object);
	
	m_MonsterInfoName = TEXT("Rampage");
	
	AIControllerClass = ARampageAIController::StaticClass();

}

// Called when the game starts or when spawned
void ARampage::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARampage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ARampage::NormalAttack()
{
	Super::NormalAttack();
	
	FVector	Loc = GetActorLocation();
	FVector	Forward = GetActorForwardVector();

	FCollisionQueryParams	params(NAME_None, false, this);

	// ������������ �� Ÿ�ֿ̹� �浹ó���� ���ֵ��� �Ѵ�.
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
		// FActorSpawnParameters	param;
		// param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//
		// ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
		// 	result.ImpactPoint, result.ImpactNormal.Rotation(), param);
		//
		// // �ּ��� �ε��Ѵ�.
		// Effect->LoadParticle(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_flash1.P_ky_flash1'"));
		//
		// // Sound
		// Effect->LoadSound(TEXT("SoundWave'/Game/Sound/Fire4.Fire4'"));


		//공격 데미지
		FDamageEvent	DmgEvent;
		float Damage = result.GetActor()->TakeDamage(m_MonsterInfo.Attack, DmgEvent, GetController(), this);
	}
}


void ARampage::UseSkill(int32 Index)
{
	Super::UseSkill(Index);

	if (!m_AnimInstance->Montage_IsPlaying(m_SkillMontageArray[Index]))
	{
		m_AnimInstance->Montage_SetPosition(m_SkillMontageArray[Index], 0.f);
		m_AnimInstance->Montage_Play(m_SkillMontageArray[Index]);
	}

	switch(Index)
	{
		default:
			break;
		
		case 0 :
			Skill1();
			break;

		case 1 :
			Skill2();
			break;

		case 2 :
			Skill3();
			break;
		case 3 :
			break;
	}
}

//얼음
void ARampage::Skill1()
{
	if(m_Target)
	{
		// 이펙트
		FVector TargetLoc = m_Target->GetActorLocation();
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
		ARampageSkill1Effect* SkillEffect = GetWorld()->SpawnActor<ARampageSkill1Effect>(ARampageSkill1Effect::StaticClass(),
			TargetLoc, FRotator::ZeroRotator, param);
		SkillEffect->Init(TEXT("RampageSkill1"), this, m_MonsterInfo.Attack);
		SkillEffect->SetLifeTime(1.5f);
	}
}

//포효
void ARampage::Skill2()
{
	// 이펙트
	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANormalEffect* Effect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(),
		GetActorLocation(), FRotator::ZeroRotator, param);
	
	Effect->LoadParticleAsync(TEXT("RampageSkill2"));
	Effect->SetEffectScale(FVector(10.f,10.f,10.f));
	Effect->LoadSoundAsync(TEXT("RampageSkill2"));

}

//돌던지기
void ARampage::Skill3()
{
	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	FTransform SocketTransform;
	int32 BoneIndex;
	const USkeletalMeshSocket* Socket = GetMesh()->GetSocketInfoByName(TEXT("RockAttachPoint"),SocketTransform, BoneIndex);
	if(Socket == nullptr)
		return;
	AActor* Skill3Rock = GetWorld()->SpawnActor<AActor>(m_Skill3RockClass, SocketTransform.GetLocation(),
		FRotator::ZeroRotator, param);
	m_Skill3Rock = Skill3Rock;
	Socket->AttachActor(Skill3Rock,GetMesh());
	
}

void ARampage::Skill2Attack()
{
	//데미지 처리
	FCollisionQueryParams params(NAME_None, false, this);
	float Radious = GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector Loc = GetActorLocation();
	FHitResult result;
	bool Sweep = GetWorld()->SweepSingleByChannel(result, Loc,
												Loc, FQuat::Identity,
												ECollisionChannel::ECC_GameTraceChannel4,
												FCollisionShape::MakeSphere(3200.f),
												params);

	if(Sweep)
	{
		FDamageEvent	DmgEvent;
		float Damage = result.GetActor()->TakeDamage(m_MonsterInfo.Attack, DmgEvent, GetController(), this);
	}
}

void ARampage::Skill3RockDetach()
{
	if(m_Skill3Rock == nullptr)
		return;
	
	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	ARampageSkill3Projectile* Projectile = GetWorld()->SpawnActor<ARampageSkill3Projectile>(ARampageSkill3Projectile::StaticClass(),
		m_Skill3Rock->GetActorLocation(), GetActorRotation(), param);
	Projectile->SetOwnerMonster(this);
	
	m_Skill3Rock->Destroy();
	m_Skill3Rock = nullptr;
}