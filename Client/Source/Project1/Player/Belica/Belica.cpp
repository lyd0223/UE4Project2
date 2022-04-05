// Fill out your copyright notice in the Description page of Project Settings.


#include "Belica.h"

#include "BelicaAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Project1GameModeBase.h"
#include "Project1/Effect/NormalEffect.h"
#include "Project1/UI/MainHUDWidget.h"
#include "Project1/UI/QuickBulletSlotWidget.h"

ABelica::ABelica()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("SkeletalMesh'/Game/ParagonLtBelica/Characters/Heroes/Belica/Skins/PolarStrike/Meshes/Belica_PolarStrike.Belica_PolarStrike'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		m_Mesh = MeshAsset.Object;
	}
	
	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("AnimBlueprint'/Game/01Resources/Player/Belica/BPBelicaAnim.BPBelicaAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	//Bullet AM Asset Load
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	NormalBulletAsset(TEXT("AnimMontage'/Game/01Resources/Player/Belica/AMBelicaAttack01.AMBelicaAttack01'"));
	if (NormalBulletAsset.Succeeded())
		m_AttackMontageMap.Add(TEXT("NormalBullet"),NormalBulletAsset.Object);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	TrippleBulletAsset(TEXT("AnimMontage'/Game/01Resources/Player/Belica/AMBelicaTrippleBullet.AMBelicaTrippleBullet'"));
	if (TrippleBulletAsset.Succeeded())
		m_AttackMontageMap.Add(TEXT("TrippleBullet"),TrippleBulletAsset.Object);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	RecoveryBulletAsset(TEXT("AnimMontage'/Game/01Resources/Player/Belica/AMBelicaRecoveryBullet.AMBelicaRecoveryBullet'"));
	if (RecoveryBulletAsset.Succeeded())
		m_AttackMontageMap.Add(TEXT("RecoveryBullet"),RecoveryBulletAsset.Object);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	PowerBulletAsset(TEXT("AnimMontage'/Game/01Resources/Player/Belica/AMBelicaPowerBullet.AMBelicaPowerBullet'"));
	if (PowerBulletAsset.Succeeded())
		m_AttackMontageMap.Add(TEXT("PowerBullet"),PowerBulletAsset.Object);
	
	m_JobName = TEXT("Belica");
}

// Called when the game starts or when spawned
void ABelica::BeginPlay()
{
	Super::BeginPlay();

	m_AnimInstance = Cast<UBelicaAnimInstance>(GetMesh()->GetAnimInstance());
	

	//Bullet 퀵슬롯...
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());

	const FBulletTableInfo* info = GameInstance->FindBulletTableInfo(TEXT("NormalBullet"));
	m_BulletQuickSlotsArray[0]=info;
	const FBulletTableInfo* info2 = GameInstance->FindBulletTableInfo(TEXT("TrippleBullet"));
	m_BulletQuickSlotsArray[1]=info2;
	const FBulletTableInfo* info3 = GameInstance->FindBulletTableInfo(TEXT("RecoveryBullet"));
	m_BulletQuickSlotsArray[2]=info3;
	const FBulletTableInfo* info4 = GameInstance->FindBulletTableInfo(TEXT("PowerBullet"));
	m_BulletQuickSlotsArray[3]=info4;

	if(!m_IsWaitingRoom)
	{
		AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(GetWorld()->GetAuthGameMode());
		for(int i = 0; i<4; i++)
		{
			UQuickBulletSlotWidget* BulletSlotWidget = GameModeBase->GetMainHUDWidget()->GetQuickSlotWidget()->GetQuickBulletSlotWidget(i);
			BulletSlotWidget->SetImage(m_BulletQuickSlotsArray[i]->IconTexture);
		}
	}
}

// Called every frame
void ABelica::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABelica::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABelica::Attack()
{
	Super::Attack();

	FString BulletName = m_BulletQuickSlotsArray[m_BulletIndex]->Name;
	UAnimMontage* animMontage = *m_AttackMontageMap.Find(BulletName);
	
	if (!m_AnimInstance->GetIsAttack() && !m_AnimInstance->Montage_IsPlaying(animMontage))
	{
		m_AnimInstance->Montage_SetPosition(animMontage, 0.f);
		m_AnimInstance->Montage_Play(animMontage);
		
		//공격속도 설정
		if(m_BulletIndex == 0)
			m_AnimInstance->Montage_SetPlayRate(animMontage, m_PlayerInfo.AttackSpeed * 1.f);
		else
			m_AnimInstance->Montage_SetPlayRate(animMontage, 1.f);
		//float PlayRate = m_AnimInstance->Montage_GetPlayRate(animMontage);
		m_AnimInstance->SetAttackEnable(true);

	}
}


void ABelica::FireNormalBullet()
{
	FVector	MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_02"));
	
	FVector CameraLoc = m_Camera->GetComponentLocation();
	FRotator CameraRot = m_Camera->GetComponentRotation();

	//카메라에서 레이 발사
	FHitResult Result;
	FCollisionQueryParams ColParam;
	ColParam.AddIgnoredActor(this);
	bool sweep = GetWorld()->LineTraceSingleByChannel(Result, CameraLoc, CameraLoc + CameraRot.Vector()* m_PlayerInfo.AttackDistance,
		ECC_GameTraceChannel5,ColParam);

	if(sweep)
	{
		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(MuzzleLoc ,Result.ImpactPoint);
		
		//디버그용 드로우
		// #if ENABLE_DRAW_DEBUG
		//
		// FVector dir = m_Camera->GetComponentRotation().Vector();
		//
		// FColor	DrawColor = FColor::Red;
		//
		// DrawDebugLine(GetWorld(), MuzzleLoc,
		// 	Result.ImpactPoint, DrawColor, false,
		// 	5.f);
		//
		// #endif

		//이펙트
		FActorSpawnParameters	SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		ANormalEffect* HitEffect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), Result.ImpactPoint, Rot,SpawnParam);
		HitEffect->LoadParticleAsync(TEXT("BelicaFireHit"));
		
		ANormalEffect* MuzzleEffect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), MuzzleLoc, Rot,SpawnParam);
		MuzzleEffect->LoadParticleAsync(TEXT("BelicaFireMuzzle"));
		MuzzleEffect->SetEffectScale(FVector(0.5f,0.5f,0.5f));
		MuzzleEffect->LoadSoundAsync(TEXT("NormalShot"));
		MuzzleEffect->SetSoundVolume(0.3f);
		
		//데미지처리
		FDamageEvent	DmgEvent;
		float AttackDamage = FMath::RandRange(m_PlayerInfo.ATK * 0.9f, m_PlayerInfo.ATK * 1.1f);
		
		float Damage = Result.GetActor()->TakeDamage(AttackDamage, DmgEvent, GetController(), this);
	}
	
}


void ABelica::FireTrippleBullet()
{
	FVector	MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_02"));
	
	FVector CameraLoc = m_Camera->GetComponentLocation();
	FRotator CameraRot = m_Camera->GetComponentRotation();

	//카메라에서 레이 발사
	FHitResult Result;
	FCollisionQueryParams ColParam;
	ColParam.AddIgnoredActor(this);
	bool sweep = GetWorld()->LineTraceSingleByChannel(Result, CameraLoc, CameraLoc + CameraRot.Vector()* m_PlayerInfo.AttackDistance,
		ECC_GameTraceChannel5,ColParam);

	if(sweep)
	{
		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(MuzzleLoc ,Result.ImpactPoint);

		//이펙트
		FActorSpawnParameters	SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		ANormalEffect* HitEffect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), Result.ImpactPoint, Rot,SpawnParam);
		HitEffect->LoadParticleAsync(TEXT("BelicaFireHit"));
		HitEffect->SetEffectScale(FVector(3.f,3.f,3.f));
		
		ANormalEffect* MuzzleEffect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), MuzzleLoc, Rot,SpawnParam);
		MuzzleEffect->LoadParticleAsync(TEXT("BelicaFireMuzzle"));
		MuzzleEffect->SetEffectScale(FVector(0.5f,0.5f,0.5f));
		MuzzleEffect->LoadSoundAsync(TEXT("TrippleShot"));
		MuzzleEffect->SetSoundVolume(0.3f);
		
		//데미지처리
		FDamageEvent	DmgEvent;
		float AttackDamage1 = FMath::RandRange(m_PlayerInfo.ATK * 0.9f, m_PlayerInfo.ATK * 1.1f);
		float Damage1 = Result.GetActor()->TakeDamage(AttackDamage1, DmgEvent, GetController(), this);
		float AttackDamage2 = FMath::RandRange(m_PlayerInfo.ATK * 0.9f, m_PlayerInfo.ATK * 1.1f);
		float Damage2 = Result.GetActor()->TakeDamage(AttackDamage2, DmgEvent, GetController(), this);
		float AttackDamage3 = FMath::RandRange(m_PlayerInfo.ATK * 0.9f, m_PlayerInfo.ATK * 1.1f);
		float Damage3 = Result.GetActor()->TakeDamage(AttackDamage3, DmgEvent, GetController(), this);

		m_PlayerInfo.SP -= 10.f;
		SetUI();
	}
	
}

void ABelica::FireRecoveryBullet()
{
	FActorSpawnParameters	SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Loc = GetActorLocation();
	Loc.Z = 0.f;
	
	ANormalEffect* HitEffect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), Loc, FRotator::ZeroRotator ,SpawnParam);
	HitEffect->LoadParticleAsync(TEXT("RecoveryBullet"));
	HitEffect->SetEffectScale(FVector(0.25f,0.25f,0.25f));
	HitEffect->LoadSoundAsync(TEXT("RecoveryShot"));
	HitEffect->SetSoundVolume(0.5f);
	
	m_PlayerInfo.SP -= 30.f;
	SetUI();
}

void ABelica::FirePowerBullet()
{
	FVector	MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));
	
	FVector CameraLoc = m_Camera->GetComponentLocation();
	FRotator CameraRot = m_Camera->GetComponentRotation();

	//카메라에서 레이 발사
	FHitResult Result;
	FCollisionQueryParams ColParam;
	ColParam.AddIgnoredActor(this);
	bool sweep = GetWorld()->LineTraceSingleByChannel(Result, CameraLoc, CameraLoc + CameraRot.Vector()* m_PlayerInfo.AttackDistance,
		ECC_GameTraceChannel5,ColParam);

	if(sweep)
	{
		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(MuzzleLoc ,Result.ImpactPoint);

		//이펙트
		FActorSpawnParameters	SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		ANormalEffect* HitEffect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), Result.ImpactPoint, Rot,SpawnParam);
		HitEffect->LoadParticleAsync(TEXT("PowerBulletHit"));
		HitEffect->SetEffectScale(FVector(2.f,2.f,2.f));
		
		ANormalEffect* MuzzleEffect = GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), MuzzleLoc, Rot,SpawnParam);
		MuzzleEffect->LoadParticleAsync(TEXT("PowerBullet"));
		MuzzleEffect->SetEffectScale(FVector(1.f,1.f, 1.f));
		MuzzleEffect->LoadSoundAsync(TEXT("PowerShot"));
		MuzzleEffect->SetSoundVolume(0.3f);
		
		//데미지처리
		FDamageEvent	DmgEvent;
		float AttackDamage = FMath::RandRange(m_PlayerInfo.ATK * 5.f * 0.9f, m_PlayerInfo.ATK * 5.f * 1.1f);
		float Damage = Result.GetActor()->TakeDamage(AttackDamage, DmgEvent, GetController(), this);

		m_PlayerInfo.SP -= 50.f;
		SetUI();
	}
	
}