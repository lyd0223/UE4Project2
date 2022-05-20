// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

UCLASS()
class PROJECT1_API ARoom : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_BoxComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class ASpawnPoint*> m_SpawnPointArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class ADoor*> m_DoorArray;

	UPROPERTY()
	class ARoomTrigger* m_RoomTrigger;
	
	//클리어시 나오는 보상 상자 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ALootBox> m_LootBoxClass;
	
	bool m_IsClear;

	int32 m_MonsterCount;
	
public:
	// Sets default values for this actor's properties
	ARoom();

public:
	class ARoomTrigger* GetRoomTrigger() const
	{
		return m_RoomTrigger;
	}
	FVector GetBoxExtent() const 
	{
		return m_BoxComponent->GetScaledBoxExtent();
	}
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	void Clear();
	
public:
	void Enter();

	void DeductMonsterCount();

};
