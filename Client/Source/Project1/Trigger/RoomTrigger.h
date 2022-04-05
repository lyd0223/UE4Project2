// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoxTrigger.h"
#include "RoomTrigger.generated.h"

UCLASS()
class PROJECT1_API ARoomTrigger : public ABoxTrigger
{
	GENERATED_BODY()
	
	public:
	ARoomTrigger();

	protected:
	class ARoom* m_OwnerRoom;

	public:
	void SetOwnerRoom(class ARoom* OwnerRoom)
	{
		m_OwnerRoom = OwnerRoom;
	}
	class ARoom* GetOwnerRoom()
	{
		return m_OwnerRoom;
	}
	
	protected:
	virtual void BeginPlay() override;

	public:
	virtual void Tick(float DeltaTime) override;

	public:
	UFUNCTION()
	void TriggerBegin();

	UFUNCTION()
	void TriggerEnd();

	void SetTriggerSize(FVector SizeVector);

	FVector2D GetTriggerSize();
};
