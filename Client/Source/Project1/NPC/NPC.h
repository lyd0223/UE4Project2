// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class PROJECT1_API ANPC : public ACharacter
{
	GENERATED_BODY()

	public:
	// Sets default values for this character's properties
	ANPC();

	protected:
	FString			m_NPCName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBillboardComponent* m_Billboard;

	class UNPCAnimInstance* m_AnimInstance;

	class ANPCTrigger* m_Trigger;

	bool m_IsActive;
	
	public:
	const FString& GetNPCName()
	{
		return m_NPCName;
	}
	class UNPCAnimInstance* GetAnim()	const
	{
		return m_AnimInstance;
	}
	UBillboardComponent* GetBillboard() const
	{
		return m_Billboard;
	}
	bool GetIsActive()
	{
		return m_IsActive;
	}
	void SetIsActive(bool IsActive)
	{
		m_IsActive = IsActive;
	}
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	public:
};
