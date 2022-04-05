// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Character.h"
#include "SelectPlayer.generated.h"

UCLASS()
class PROJECT1_API ASelectPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASelectPlayer();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerJob m_PlayerJob;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMesh* m_Mesh;
	
	class USelectPlayerAnimInstance* m_AnimInstance;
public:
	EPlayerJob GetPlayerJob() const
	{
		return m_PlayerJob;
	}
	class USelectPlayerAnimInstance* GetAnimInstance() const
	{
		return m_AnimInstance;
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
