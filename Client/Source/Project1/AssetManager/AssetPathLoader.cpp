// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetPathLoader.h"

UAssetPathLoader::UAssetPathLoader()
{
}


void UAssetPathLoader::ConvertPath()
{
	for (auto& result : MaterialPathArray)
	{
		m_mapMaterialPath.Add(result.Name, result.Path);
		LOG(TEXT("Name : %s Path : %s"), *result.Name, *result.Path.ToString());
	}

	for (auto& result : ParticlePathArray)
	{
		m_mapParticlePath.Add(result.Name, result.Path);
		LOG(TEXT("Name : %s Path : %s"), *result.Name, *result.Path.ToString());
	}

	for (auto& result : SoundPathArray)
	{
		m_mapSoundPath.Add(result.Name, result.Path);
		LOG(TEXT("Name : %s Path : %s"), *result.Name, *result.Path.ToString());
	}
	
	for (auto& result : TexturePathArray)
	{
		m_mapTexturePath.Add(result.Name, result.Path);
		LOG(TEXT("Name : %s Path : %s"), *result.Name, *result.Path.ToString());
	}
}

const FSoftObjectPath* UAssetPathLoader::FindMaterialPath(const FString& Name)
{
	return m_mapMaterialPath.Find(Name);
}

const FSoftObjectPath* UAssetPathLoader::FindSoundPath(const FString& Name)
{
	return m_mapSoundPath.Find(Name);
}

const FSoftObjectPath* UAssetPathLoader::FindParticlePath(const FString& Name)
{
	return m_mapParticlePath.Find(Name);
}

const FSoftObjectPath* UAssetPathLoader::FindTexturePath(const FString& Name)
{
	return m_mapTexturePath.Find(Name);
}
