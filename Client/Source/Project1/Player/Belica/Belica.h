// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../PlayerCharacter.h"
#include "Belica.generated.h"

UCLASS()
class PROJECT1_API ABelica : public APlayerCharacter
{
	GENERATED_BODY()
	
	public:
	// Sets default values for this character's properties
	ABelica();

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FString, UAnimMontage*> m_AttackMontageMap;
	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	protected:
	virtual void Attack() override;

	public:
	void FireNormalBullet();
	void FireTrippleBullet();
	void FireRecoveryBullet();
	void FirePowerBullet();
};
