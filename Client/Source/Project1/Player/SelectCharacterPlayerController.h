// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "SelectCharacterPlayerController.generated.h"

UCLASS()
class PROJECT1_API ASelectCharacterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
	ASelectCharacterPlayerController();

	private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<class ASelectPlayer*> m_SelectCharacterArray;

	
	public:
	void AddSelectCharacter(class ASelectPlayer* SelectCharacter)
	{
		m_SelectCharacterArray.Add(SelectCharacter);
	}
	public:
	virtual void PlayerTick(float DeltaTime);
	virtual void SetupInputComponent();

	public:
	void Move(EPlayerJob PlayerJob);
};
