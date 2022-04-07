// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientBlueprintFunctionLibrary.h"


bool UClientBlueprintFunctionLibrary::FStringToUTF8(const FString& _FString, std::string& _UTF8)
{
	ANSICHAR* Ptr = TCHAR_TO_UTF8(*_FString);
	_UTF8 = std::string(Ptr);
	return true;
}

bool UClientBlueprintFunctionLibrary::StringToVectorData(const std::string& _String, std::vector<uint8> _VectorData)
{
	_VectorData.clear();
	_VectorData.resize(_String.size() + 1);
	_VectorData[_String.size()] = 0;
	std::copy(_String.begin(), _String.end(), _VectorData.begin());

	return true;
}

bool UClientBlueprintFunctionLibrary::UTF8ToFString(const std::string& _UTF8, FString& _FString)
{
	_FString = FString(UTF8_TO_TCHAR(&_UTF8[0]));
	return true;
}

bool UClientBlueprintFunctionLibrary::FStringToVectorData(const FString& _FString, std::vector<uint8> _VectorData)
{
	std::string Text = "";
	FStringToUTF8(_FString, Text);
	StringToVectorData(Text, _VectorData);

	return true;
	
}