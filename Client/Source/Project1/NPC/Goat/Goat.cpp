// Fill out your copyright notice in the Description page of Project Settings.


#include "Goat.h"

AGoat::AGoat()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("SkeletalMesh'/Game/Goat/Base.Base'"));
	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimAsset(TEXT("AnimBlueprint'/Game/01Resources/NPC/Goat/BPGoatAnim.BPGoatAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	m_NPCName = TEXT("Goat");
}


// Called when the game starts or when spawned
void AGoat::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGoat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
