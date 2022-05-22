// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDescWidget.h"

#include "SelectCharacterMainWidget.h"
#include "../../Project1GameInstance.h"
#include "Components/CanvasPanelSlot.h"


void UCharacterDescWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_DescText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DescText")));
	m_BackgroundImage1 = Cast<UImage>(GetWidgetFromName(TEXT("BackgroundImage1")));
	m_BackgroundImage2 = Cast<UImage>(GetWidgetFromName(TEXT("BackgroundImage2")));
	
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
		
		//크기 변경
		m_BackgroundImage1->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		m_BackgroundImage2->SetVisibility(ESlateVisibility::Collapsed);

		//스탯그래프 off
		m_OwnerWidget->CharacterStatGraphOn(true);

		m_OwnerWidget->EnterButtonOn(false);
		return;
	}
	FString String = TEXT("");
	FString Nickname = TEXT("");
	UClientBlueprintFunctionLibrary::UTF8ToFString(CharacterInfo->m_Nickname, Nickname);
	String += FString::Printf(TEXT("캐릭터이름 : %s\n"), *Nickname);
	String += FString::Printf(TEXT("LV\t : %d\n"), CharacterInfo->m_LV);
	String += FString::Printf(TEXT("EXP\t : %d\n"), CharacterInfo->m_EXP);
	String += FString::Printf(TEXT("HP\t : %d\n"), static_cast<int>(CharacterInfo->m_HP));
	String += FString::Printf(TEXT("MP\t : %d\n"), static_cast<int>(CharacterInfo->m_SP));
	String += FString::Printf(TEXT("ATK\t : %d\n"), static_cast<int>(CharacterInfo->m_ATK));
	String += FString::Printf(TEXT("DEF\t : %d\n"), static_cast<int>(CharacterInfo->m_DEF));
	String += FString::Printf(TEXT("AttackSpeed\t : %.2f\n"), CharacterInfo->m_AttackSpeed);
	String += FString::Printf(TEXT("MoveSpeed\t : %d\n"), static_cast<int>(CharacterInfo->m_MoveSpeed));

	FString ClassName = TEXT("");
	UClientBlueprintFunctionLibrary::UTF8ToFString(CharacterInfo->m_ClassName, ClassName);
	
	m_NameText->SetText(FText::FromString(ClassName));
	m_DescText->SetText(FText::FromString(String));

	//크기 변경
	m_BackgroundImage1->SetVisibility(ESlateVisibility::Collapsed);
	m_BackgroundImage2->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	//스탯그래프 off
	m_OwnerWidget->CharacterStatGraphOn(false);
	
	m_OwnerWidget->EnterButtonOn(true);
}
