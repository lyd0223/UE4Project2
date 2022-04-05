// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostCharacter.h"

// Sets default values
AGhostCharacter::AGhostCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Mesh"));
	SetRootComponent(m_Mesh);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("MaterialInstanceConstant'/Game/01Resources/Materials/MTGhostCharacter_Inst.MTGhostCharacter_Inst'"));
	if(MaterialAsset.Succeeded())
		m_Material = MaterialAsset.Object;

	m_Time = 1.f;
	m_AccTime = 0.f;
	m_Color = FLinearColor(0.f, 5.f, 10.f , 0.f);
}

// Called when the game starts or when spawned
void AGhostCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGhostCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_AccTime += DeltaTime;

	if(m_AccTime >= m_Time)
		Destroy();
	
	float Opacity = 1- m_AccTime / m_Time;
	
	for(auto Material : m_MaterialArray)
	{
		Material->SetScalarParameterValue(TEXT("Opacity"), Opacity);
	}
	
}

void AGhostCharacter::SetMesh(USkeletalMesh* Mesh)
{
	m_Mesh->SetSkeletalMesh(Mesh);
	
	for(int32 i = 0; i < m_Mesh->GetNumMaterials(); i++)
	{
		UMaterialInstanceDynamic* MaterialInstanceDynamic = m_Mesh->CreateDynamicMaterialInstance(i, m_Material);
		m_MaterialArray.Add(MaterialInstanceDynamic);
	}
	
}


void AGhostCharacter::CopyAnimation(USkeletalMeshComponent* MeshComponent)
{
	m_Mesh->CopyPoseFromSkeletalComponent(MeshComponent);
}