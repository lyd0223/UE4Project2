// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "WaitingRoomGameModeBase.generated.h"

UCLASS()
class PROJECT1_API AWaitingRoomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
	AWaitingRoomGameModeBase();

	protected:
	TArray<TSubclassOf<APawn>>	m_PlayerClassArray;

	TSubclassOf<class UWaitingRoomMainWidget> m_MainWidgetClass;
	
	class UWaitingRoomMainWidget* m_MainWidget;
	
	public:
	UWaitingRoomMainWidget* GetMainWidget() const
	{
		return m_MainWidget;
	}

	public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void BeginPlay() override;
};
