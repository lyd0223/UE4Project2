// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDescWidget.h"
#include "../../Project1GameInstance.h"


void UCharacterDescWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_DescText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DescText")));
	
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());
	UDataTable* DataTable = GameInstance->GetSelectPlayerInfoTable();
	TArray<FName> NameArray = DataTable->GetRowNames();
	for(auto& Name : NameArray)
	{
		FSelectPlayerTableInfo* TableInfo = DataTable->FindRow<FSelectPlayerTableInfo>(Name, "");
		m_SelectPlayerTableInfoMap.Add(TableInfo->PlayerJob,*TableInfo);
	}

	//초기화
	FSelectPlayerTableInfo* TableInfo = m_SelectPlayerTableInfoMap.Find(EPlayerJob::Belica);
	m_NameText->SetText(FText::FromString(TableInfo->Name));
	m_DescText->SetText(FText::FromString(TableInfo->Desc));
}

void UCharacterDescWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UCharacterDescWidget::SetDesc(EPlayerJob PlayerJob)
{
	FSelectPlayerTableInfo* TableInfo = m_SelectPlayerTableInfoMap.Find(PlayerJob);
	m_NameText->SetText(FText::FromString(TableInfo->Name));
	m_DescText->SetText(FText::FromString(TableInfo->Desc));
}