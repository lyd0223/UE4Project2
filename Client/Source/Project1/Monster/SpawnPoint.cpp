// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "Monster.h"
#include "MonsterAnimInstance.h"
#include "../Map/Room.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	m_Monster = nullptr;
	m_OwnerRoom = nullptr;
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASpawnPoint::SpawnMonster()
{
	if (m_MonsterClass)
	{
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AMonster* Monster = GetWorld()->SpawnActor<AMonster>(m_MonsterClass,
			GetActorLocation(), GetActorRotation(), param);
		
		Monster->GetAnim()->ChangeAnimType(EMonsterAnimType::Spawn);

		Monster->SetSpawnPoint(this);
		m_Monster = Monster;
	}
}

void ASpawnPoint::Death()
{
	m_Monster = nullptr;
	m_OwnerRoom->DeductMonsterCount();
}
