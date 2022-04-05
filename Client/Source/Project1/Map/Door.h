// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class PROJECT1_API ADoor : public AActor
{
	GENERATED_BODY()

protected:

	UStaticMeshComponent* m_RightDoor;
	UStaticMeshComponent* m_LeftDoor;
	
	FTimerHandle m_TimerHandle;

public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public :
	void Open();
	void Close();


protected:
	void DoorOpen();
	void DoorClose();
};
