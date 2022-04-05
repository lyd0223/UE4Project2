// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionGunner.h"
#include "MinionGunnerAIController.h"
#include "Project1/Effect/Projecttiles/MinionGunnerAttackProjectile.h"

AMinionGunner::AMinionGunner()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Ranged_Dusk.Minion_Lane_Ranged_Dusk'"));
	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	
	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("AnimBlueprint'/Game/01Resources/Monster/MinionGunner/BPMinionGunnerAnim.BPMinionGunnerAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	m_MonsterInfoName = TEXT("MinionGunner");
	
	AIControllerClass = AMinionGunnerAIController::StaticClass();

}

// Called when the game starts or when spawned
void AMinionGunner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMinionGunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMinionGunner::NormalAttack()
{
	FVector	MuzzleLoc = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));
	
	// 총알 스폰
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AMinionGunnerAttackProjectile* Bullet = GetWorld()->SpawnActor<AMinionGunnerAttackProjectile>(
		AMinionGunnerAttackProjectile::StaticClass(), MuzzleLoc, GetActorRotation(),
		SpawnParam);
	Bullet->SetOwnerMonster(this);
		
	
}