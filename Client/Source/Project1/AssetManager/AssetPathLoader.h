// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "AssetPathLoader.generated.h"

UCLASS(Config=AssetAddress)
class PROJECT1_API UAssetPathLoader : public UObject
{
	GENERATED_BODY()

public:
	UAssetPathLoader();

private:
	UPROPERTY(Config)
	TArray<FAssetPathInfo> MaterialPathArray;

	UPROPERTY(Config)
	TArray<FAssetPathInfo> ParticlePathArray;

	UPROPERTY(Config)
	TArray<FAssetPathInfo> SoundPathArray;

	UPROPERTY(Config)
	TArray<FAssetPathInfo> TexturePathArray;

	TMap<FString, FSoftObjectPath> m_mapMaterialPath;
	TMap<FString, FSoftObjectPath> m_mapParticlePath;
	TMap<FString, FSoftObjectPath> m_mapSoundPath;
	TMap<FString, FSoftObjectPath> m_mapTexturePath;


public:
	void ConvertPath();
	const FSoftObjectPath* FindMaterialPath(const FString& Name);
	const FSoftObjectPath* FindSoundPath(const FString& Name);
	const FSoftObjectPath* FindParticlePath(const FString& Name);
	const FSoftObjectPath* FindTexturePath(const FString& Name);
};
