
#include "Gunner.h"
#include "../PlayerCharacter.h"
#include "GunnerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Project1/Effect/Projecttiles/GunnerNormalAttackProjectile.h"

AGunner::AGunner()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	GunnerMeshAsset(TEXT("SkeletalMesh'/Game/ParagonRevenant/Characters/Heroes/Revenant/Meshes/Revenant.Revenant'"));
	if (GunnerMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(GunnerMeshAsset.Object);
		m_Mesh = GunnerMeshAsset.Object;
	}
	
	static ConstructorHelpers::FClassFinder<UAnimInstance>	GunnerAnimAsset(TEXT("AnimBlueprint'/Game/01Resources/Player/Gunner/BPGunnerAnim.BPGunnerAnim_C'"));
	if (GunnerAnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(GunnerAnimAsset.Class);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	AttackFastAsset(TEXT("AnimMontage'/Game/01Resources/Player/Gunner/AMAttack01.AMAttack01'"));
	if (AttackFastAsset.Succeeded())
		m_AttackMontageMap.Add(TEXT("AttackFast"),AttackFastAsset.Object);

	m_JobName = TEXT("Gunner");
}

// Called when the game starts or when spawned
void AGunner::BeginPlay()
{
	Super::BeginPlay();

	m_AnimInstance = Cast<UGunnerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AGunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGunner::Attack()
{
	Super::Attack();

	UAnimMontage* animMontage = *m_AttackMontageMap.Find(TEXT("AttackFast"));
	
	if (!m_AnimInstance->GetIsAttack() && !m_AnimInstance->Montage_IsPlaying(animMontage))
	{
		m_AnimInstance->Montage_SetPosition(animMontage, 0.f);
		m_AnimInstance->Montage_Play(animMontage);

		//공격속도 설정
		m_AnimInstance->Montage_SetPlayRate(animMontage, m_PlayerInfo.AttackSpeed);
		//float PlayRate = m_AnimInstance->Montage_GetPlayRate(animMontage);
		m_AnimInstance->SetAttackEnable(true);

	}
}


void AGunner::FireNormalAttackBullet()
{
	FVector	MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_02"));
	
	FVector CameraLoc = m_Camera->GetComponentLocation();
	FRotator CameraRot = m_Camera->GetComponentRotation();

	//카메라에서 레이 발사
	FHitResult Result;
	FCollisionQueryParams ColParam;
	ColParam.AddIgnoredActor(this);
	bool sweep = GetWorld()->LineTraceSingleByChannel(Result, CameraLoc, CameraLoc + CameraRot.Vector()*10000.f,
		ECollisionChannel::ECC_Visibility,ColParam);

	if(sweep)
	{
		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(MuzzleLoc ,Result.ImpactPoint);
		
		//디버그용 드로우
		#if ENABLE_DRAW_DEBUG

		FVector dir = m_Camera->GetComponentRotation().Vector();
	
		FColor	DrawColor = FColor::Red;
	
		DrawDebugLine(GetWorld(), MuzzleLoc,
			Result.ImpactPoint, DrawColor, false,
			5.f);
	
		#endif

		FActorSpawnParameters	SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AGunnerNormalAttackProjectile* Bullet = GetWorld()->SpawnActor<AGunnerNormalAttackProjectile>(
			AGunnerNormalAttackProjectile::StaticClass(), MuzzleLoc, Rot,
			SpawnParam);

		Bullet->SetOwnerPlayer(this);
		
	}
	
}