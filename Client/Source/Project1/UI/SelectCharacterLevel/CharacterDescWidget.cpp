// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDescWidget.h"

#include "SelectCharacterMainWidget.h"
#include "../../Project1GameInstance.h"


void UCharacterDescWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_DescText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DescText")));

	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());
	UDataTable* DataTable = GameInstance->GetSelectPlayerInfoTable();
	TArray<FName> NameArray = DataTable->GetRowNames();
	for (auto& Name : NameArray)
	{
		FSelectPlayerTableInfo* TableInfo = DataTable->FindRow<FSelectPlayerTableInfo>(Name, "");
		m_SelectPlayerTableInfoMap.Add(TableInfo->PlayerJob, *TableInfo);
	}

	//초기화
	FSelectPlayerTableInfo* TableInfo = m_SelectPlayerTableInfoMap.Find(EPlayerJob::Belica);
	m_NameText->SetText(FText::FromString(TableInfo->Name));
	m_DescText->SetText(FText::FromString(TableInfo->Desc));

	m_OwnerWidget= nullptr;
}

void UCharacterDescWidget::SetDesc(EPlayerJob PlayerJob, const TMap<EPlayerJob, FCharacterInfo>& _CharacterInfoMap)
{
	const FCharacterInfo* CharacterInfo = _CharacterInfoMap.Find(PlayerJob);
	if (CharacterInfo == nullptr)
	{
		FSelectPlayerTableInfo* TableInfo = m_SelectPlayerTableInfoMap.Find(PlayerJob);
		m_NameText->SetText(FText::FromString(TableInfo->Name));
		m_DescText->SetText(FText::FromString(TableInfo->Desc));
		m_OwnerWidget->EnterButtonOn(false);
		return;
	}
	FString String = TEXT("");
	FString Nickname = TEXT("");
	UClientBlueprintFunctionLibrary::UTF8ToFString(CharacterInfo->m_Nickname, Nickname);
	String += FString::Printf(TEXT("캐릭터이름 : %s\n"), *Nickname);
	String += FString::Printf(TEXT("LV\t : %d\n"), CharacterInfo->m_LV);
	String += FString::Printf(TEXT("HP\t : %d\n"), static_cast<int>(CharacterInfo->m_HP));
	String += FString::Printf(TEXT("MP\t : %d\n"), static_cast<int>(CharacterInfo->m_MP));
	String += FString::Printf(TEXT("ATK\t : %d\n"), static_cast<int>(CharacterInfo->m_ATK));

	FString ClassName = TEXT("");
	UClientBlueprintFunctionLibrary::UTF8ToFString(CharacterInfo->m_ClassName, ClassName);
	
	m_NameText->SetText(FText::FromString(ClassName));
	m_DescText->SetText(FText::FromString(String));
	m_OwnerWidget->EnterButtonOn(true);
}
