// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

DECLARE_DELEGATE(FRoomDeligate);
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ARoomTrigger* m_RoomTrigger;
	
	bool m_IsClear;

	int32 m_MonsterCount;

	//Minimap Room 세팅 델리게이트
	FRoomDeligate m_RoomDeligate;
	FTimerHandle m_RegisterTimerHandle;

	//클리어시 나오는 보상 상자 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ALootBox> m_LootBoxClass;
	
	
	
public:
	// Sets default values for this actor's properties
	ARoom();

public:
	class ARoomTrigger* GetRoomTrigger()
	{
		return m_RoomTrigger;
	}
	FVector GetBoxExtent()
	{
		return m_BoxComponent->GetScaledBoxExtent();
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void Clear();
public:
	void Enter();

	void DeductMonsterCount();

	template <typename T>
	void SetRoomDelegate(T* Obj, void (T::* Func)())
	{
		m_RoomDeligate.BindUObject(Obj, Func);
	}

	//void RegisterRoomintoMinimap();
};
