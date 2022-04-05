// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "SelectCharacterGameModeBase.generated.h"

UCLASS()
class PROJECT1_API ASelectCharacterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
	ASelectCharacterGameModeBase();

	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class USelectCharacterMainWidget>	m_SelectCharacterMainWidgetClass;

	class USelectCharacterMainWidget* m_SelectCharacterMainWidget;

	public:
	class USelectCharacterMainWidget* GetSelectHUD()
	{
		return m_SelectCharacterMainWidget;
	}

	public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void BeginPlay() override;
};
