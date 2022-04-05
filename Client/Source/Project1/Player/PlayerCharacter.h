// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PROJECT1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* m_Arm;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// USceneCaptureComponent2D* m_MinimapSceneCapture2D;

	
	class UPlayerAnimInstance* m_AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FPlayerInfo m_PlayerInfo;

	FString m_JobName;
	
	bool m_MoveKey;
	bool m_AttackEnable;

	//UI모드일시 화면회전, 키입력 등을 막기 위한 용도
	bool m_IsUIMode;

	//대쉬 리본트레일 효과
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* m_TrailParticle;
	
	//잔상효과
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		m_GhostTrailTime;
	FTimerHandle m_GhostTrailTimerHandle;
	USkeletalMesh* m_Mesh;
	
	//몬스터,방,문 탐색을위한 타이머핸들
	FTimerHandle m_DetectMonsterHandle;
	FTimerHandle m_DetectRoomHandle;
	FTimerHandle m_DetectDoorHandle;

	//WaitingRoomLevel일때의 처리를 하기위한 bool변수
	bool m_IsWaitingRoom;

	//초당 SP회복을위한 타이머핸들
	FTimerHandle m_SPRecoveryHandle;

	//Bullet 전환을위한 Index
	uint8 m_BulletIndex;

	//퀵슬롯
	TArray<FItem*> m_ItemQuickSlotsArray;
	TArray<const FBulletTableInfo*> m_BulletQuickSlotsArray;

	//렌더타겟
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneCaptureComponent2D* m_SceneCaputreComponent;

	
	public:
	FPlayerInfo& GetPlayerInfo()
	{
		return m_PlayerInfo;
	}
	void SetIsWaitingRoom(bool IsWaitingRoom)
	{
		m_IsWaitingRoom = IsWaitingRoom;
	}
	void SetIsUIMode(bool IsUIMode)
	{
		m_IsUIMode = IsUIMode;
	}
	void SetItemQuickSlot(uint8 Index, FItem* Item)
	{
		if(m_ItemQuickSlotsArray.Num() > Index)
		{
			m_ItemQuickSlotsArray[Index] = Item;
		}
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	void MoveFrontKey(float Scale);
	void MoveRightKey(float Scale);
	void RotationZKey(float Scale);
	void CameraZoomKey(float Scale);
	void CameraRotationYKey(float Scale);

	void JumpKey();
	void AttackKey();
	void MenuKey();
	void DashKey();
	void BulletQuickSlotLeftKey();
	void BulletQuickSlotRightKey();
	void ItemQuickSlot1Key();
	void ItemQuickSlot2Key();
	void ItemQuickSlot3Key();
	void ItemQuickSlot4Key();
	void ItemQuickSlot5Key();

protected:
	virtual void Attack();
	void SPRecovery();
	virtual void GhostTrailOn();
	virtual void GhostTrailOff();
	void GhostTrailFunc();
	
public:
	void SetUI();
	
	virtual void AttackEnd();
	virtual void DashEnd();

	//미니맵에서 쓰기 위한 몬스터 / 방 탐색.
	UFUNCTION()
	void DetectMonster();
	UFUNCTION()
	void DetectRoom();
	UFUNCTION()
	void DetectDoor();
};
