// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "Project1GameModeBase.generated.h"

UCLASS()
class PROJECT1_API AProject1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProject1GameModeBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UMainHUDWidget>	m_MainHUDWidgetClass;
	class UMainHUDWidget* m_MainHUDWidget;
	
	TArray<TSubclassOf<APawn>>	m_PlayerClassArray;

	class UAssetPathLoader* m_AssetPathLoader;
	
public:
	class UMainHUDWidget* GetMainHUDWidget() const
	{
		return m_MainHUDWidget;
	}
public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void BeginPlay() override;
};
