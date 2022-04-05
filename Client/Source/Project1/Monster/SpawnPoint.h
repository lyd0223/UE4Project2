// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"

#include "SpawnPoint.generated.h"

UCLASS()
class PROJECT1_API ASpawnPoint : public AActor
{
	GENERATED_BODY()

public :
	ASpawnPoint();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMonster> m_MonsterClass;

	class AMonster* m_Monster;

	class ARoom* m_OwnerRoom;

public:
	void SetOwnerRoom(class ARoom* OwnerRoom)
	{
		m_OwnerRoom = OwnerRoom;
	}
	
public:
	void Death();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SpawnMonster();
};
