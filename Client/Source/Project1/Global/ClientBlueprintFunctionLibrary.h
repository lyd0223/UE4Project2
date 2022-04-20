// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <string>
#include <vector>
#include "ClientBlueprintFunctionLibrary.generated.h"

UCLASS()
class PROJECT1_API UClientBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:
	static bool FStringToUTF8(const FString& _FString, std::string& _UTF8);
	static bool StringToVectorData(const std::string& _String, std::vector<uint8> _VectorData);
	static bool UTF8ToFString(const std::string& _UTF8, FString& _FString);
	static bool FStringToVectorData(const FString& _FString, std::vector<uint8> _VectorData);
};
