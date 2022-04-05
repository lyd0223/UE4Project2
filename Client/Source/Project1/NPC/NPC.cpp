// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "Project1/Trigger/NPCTrigger.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//콜리전 설정
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NPC"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	//빌보드
	m_Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	m_Billboard->SetupAttachment(GetRootComponent());

	//NPC트리거
	m_Trigger = nullptr;

	//플레이어 근접시 활성화되는 변수
	m_IsActive = false;
	
	//데칼 비활성화
	GetMesh()->bReceivesDecals = false;
	
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	//NPC트리거 스폰
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	m_Trigger = GetWorld()->SpawnActor<ANPCTrigger>(ANPCTrigger::StaticClass(), GetActorLocation(),
														GetActorRotation(), param);
	m_Trigger->SetTriggerSize(500.f);
	m_Trigger->SetOwnerNPC(this);

}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}