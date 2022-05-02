// Fill out your copyright notice in the Description page of Project Settings.


#include "DeleteCheckWidget.h"

#include "Project1/Project1GameInstance.h"
#include "Project1/Global/Message/ClientToServer.h"
#include "Project1/UI/SelectCharacterLevel/SelectCharacterMainWidget.h"


void UDeleteCheckWidget::NativeConstruct()
{
	m_DeleteButton = Cast<UButton>(GetWidgetFromName(TEXT("DeleteButton")));
	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	m_DeleteButton->OnClicked.AddDynamic(this, &UDeleteCheckWidget::DeleteButtonClicked);
	m_CloseButton->OnClicked.AddDynamic(this, &UDeleteCheckWidget::CloseButtonClicked);
	m_OwnerWidget = nullptr;
}
	
void UDeleteCheckWidget::DeleteButtonClicked()
{
	//서버로 캐릭터인포삭제 패킷 보내기.--------------------------------------------------------
	UProject1GameInstance* GameInst = Cast<UProject1GameInstance>(GetGameInstance());
	if (GameInst->GetIsClientMode())
		return;
	DeleteCharacterInfoMessage Message;

	FCharacterInfo* CharacterInfo = m_OwnerWidget->GetCharacterInfoMap().Find(m_OwnerWidget->GetSelectJob());
	Message.m_CharacterInfo = *CharacterInfo;

	GameServerSerializer Serializer;
	Message.Serialize(Serializer);

	if (!GameInst->Send(Serializer.GetData()))
	{
		PrintViewport(2.f, FColor::Red, TEXT("DeleteCharacterInfoMessage Send Error!"));
	}
	//--------------------------------------------------------------------------------------
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UDeleteCheckWidget::CloseButtonClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}