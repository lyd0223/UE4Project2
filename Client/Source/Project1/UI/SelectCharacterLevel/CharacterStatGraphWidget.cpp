// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatGraphWidget.h"

#include "Project1/Project1GameInstance.h"


void UCharacterStatGraphWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_StatGraphImage = Cast<UImage>(GetWidgetFromName(TEXT("StatGraphImage")));

	
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
	m_StatGraphImage->SetBrushFromTexture(TableInfo->StatGraphTexture);
}

void UCharacterStatGraphWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UCharacterStatGraphWidget::SetStatGraphImage(EPlayerJob PlayerJob)
{
	FSelectPlayerTableInfo* TableInfo = m_SelectPlayerTableInfoMap.Find(PlayerJob);
	m_StatGraphImage->SetBrushFromTexture(TableInfo->StatGraphTexture);
}