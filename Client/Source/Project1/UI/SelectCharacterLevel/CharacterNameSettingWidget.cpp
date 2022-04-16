// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterNameSettingWidget.h"
#include "SelectCharacterMainWidget.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Global/Message/ClientToServer.h"

void UCharacterNameSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_CreateButton = Cast<UButton>(GetWidgetFromName(TEXT("CreateButton")));
	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	m_CreateButton->OnClicked.AddDynamic(this, &UCharacterNameSettingWidget::CreateButtonClicked);
	m_CloseButton->OnClicked.AddDynamic(this, &UCharacterNameSettingWidget::CloseButtonClicked);

	m_NameTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("NameTextBox")));
	m_NameTextBox->OnTextChanged.AddDynamic(this, &UCharacterNameSettingWidget::NameTextBoxChanged);
	m_NameString = TEXT("");

	m_OwnerWidget = nullptr;
}

void UCharacterNameSettingWidget::CreateButtonClicked()
{
	//서버로 캐릭터인포 생성 패킷 보내기.--------------------------------------------------------
	UProject1GameInstance* GameInst = Cast<UProject1GameInstance>(GetGameInstance());
	if (GameInst->GetIsClientMode())
		return;
	CreateCharacterInfoMessage Message;

	//캐릭터 정보 불러오기
	FString ClassName = TEXT("");

	switch (m_OwnerWidget->GetSelectJob())
	{
	case EPlayerJob::Belica:
		ClassName = TEXT("Belica");
		break;
	case EPlayerJob::Revenant:
		ClassName = TEXT("Revenant");
		break;
	case EPlayerJob::Wraith:
		ClassName = TEXT("Wraith");
		break;
	case EPlayerJob::TwinBlaster:
		ClassName = TEXT("TwinBlaster");
		break;
	case EPlayerJob::Gunner:
		break;
	case EPlayerJob::End:
		break;
	}

	const FPlayerTableInfo* Info = GameInst->FindPlayerInfo(ClassName);

	FCharacterInfo& CharacterInfo = Message.m_CharacterInfo;
	if (Info)
	{
		CharacterInfo.m_UserIdx = GameInst->GetUserIdx();
		UClientBlueprintFunctionLibrary::FStringToUTF8(m_NameString, CharacterInfo.m_Nickname);
		UClientBlueprintFunctionLibrary::FStringToUTF8(ClassName, CharacterInfo.m_ClassName);
		CharacterInfo.m_LV = Info->Level;
		CharacterInfo.m_HP = Info->HPMax;
		CharacterInfo.m_MP = Info->SPMax;
		CharacterInfo.m_ATK = Info->ATK;
		// m_PlayerInfo.SPMax = Info->SPMax;
		// m_PlayerInfo.EXP = Info->EXP;
		// m_PlayerInfo.DEF = Info->DEF;
		// m_PlayerInfo.AttackSpeed = Info->AttackSpeed;
		//m_PlayerInfo.MoveSpeed = Info->MoveSpeed;
	}

	GameServerSerializer Serializer;
	Message.Serialize(Serializer);

	if (!GameInst->Send(Serializer.GetData()))
	{
		PrintViewport(2.f, FColor::Red, TEXT("CreateCharacterInfo Message Send Error!"));
	}
	//--------------------------------------------------------------------------------------
}

void UCharacterNameSettingWidget::CloseButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UCharacterNameSettingWidget::NameTextBoxChanged(const FText& Text)
{
	m_NameString = Text.ToString();
}
