// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSceneCapture2D.h"

#include "Project1/Project1GameInstance.h"
#include "Project1/Effect/NormalEffect.h"


AMenuSceneCapture2D::AMenuSceneCapture2D()
{
	m_BelicaMeshActor = nullptr;
	m_RevenantMeshActor = nullptr;
	m_WraithMeshActor = nullptr;
	m_TwinBlastMeshActor = nullptr;
	m_Distance = 100.f;

}

void AMenuSceneCapture2D::BeginPlay()
{
	Super::BeginPlay();
	
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetGameInstance());
	if (GameInstance == nullptr)
		return;
	EPlayerJob SelectPlayerJob = GameInstance->GetSelectJob();
	AActor* MeshActor = nullptr;
	switch (SelectPlayerJob)
	{
		case EPlayerJob::Belica :
			MeshActor = m_BelicaMeshActor;
			break;
		case EPlayerJob::Revenant :
			MeshActor = m_RevenantMeshActor;
			break;
		case EPlayerJob::Wraith :
			MeshActor = m_WraithMeshActor;
			break;
		case EPlayerJob::TwinBlaster :
			MeshActor = m_TwinBlastMeshActor;
			break;
		case EPlayerJob::Gunner :
			MeshActor = m_RevenantMeshActor;
			break;
		case EPlayerJob::End :
			break;
	}
	FVector Loc = MeshActor->GetActorLocation();
	Loc.Y += m_Distance;
	Loc.Z += 120.f;
	SetActorLocation(Loc);
}
