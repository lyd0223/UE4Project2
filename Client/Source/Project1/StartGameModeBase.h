// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameModeBase.generated.h"

UCLASS()
class PROJECT1_API AStartGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
	AStartGameModeBase();
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UStartMainWidget>	m_StartHUDClass;

	class UStartMainWidget* m_StartHUD;

	public:
	class UStartMainWidget* GetStartHUD()
	{
		return m_StartHUD;
	}

	public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void BeginPlay() override;
};
