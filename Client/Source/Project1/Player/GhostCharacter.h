// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GhostCharacter.generated.h"

UCLASS()
class PROJECT1_API AGhostCharacter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGhostCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPoseableMeshComponent* m_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* m_Material;

	TArray<UMaterialInstanceDynamic*> m_MaterialArray;
	
	float m_Time;
	float m_AccTime;
	
	FLinearColor m_Color;
public:
	void SetMesh(USkeletalMesh* Mesh);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	public :
	void CopyAnimation(USkeletalMeshComponent* MeshComponent);
};
