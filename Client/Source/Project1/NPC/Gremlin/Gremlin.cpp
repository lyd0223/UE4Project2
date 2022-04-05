// Fill out your copyright notice in the Description page of Project Settings.


#include "Gremlin.h"


AGremlin::AGremlin()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("SkeletalMesh'/Game/Gremlin/Gremlin.Gremlin'"));
	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("AnimBlueprint'/Game/01Resources/NPC/Gremlin/BPGremlinAnim.BPGremlinAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	m_NPCName = TEXT("Gremlin");
}


// Called when the game starts or when spawned
void AGremlin::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGremlin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
