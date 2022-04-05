// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "WaitingRoomPlayerController.generated.h"

UCLASS()
class PROJECT1_API AWaitingRoomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
	AWaitingRoomPlayerController();

	protected:
	class ANPC* m_TargetNPC;

	public:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime);
	void OpenWidget();
};
