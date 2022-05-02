// Fill out your copyright notice in the Description page of Project Settings.


#include "DeleteCheckWidget.h"


void UDeleteCheckWidget::NativeConstruct()
{

}
	
void UDeleteCheckWidget::DeleteButtonClicked()
{
	//서버로 캐릭터인포삭제 패킷 보내기.--------------------------------------------------------
	UProject1GameInstance* GameInst = Cast<UProject1GameInstance>(GetGameInstance());
	if (GameInst->GetIsClientMode())
		return;
	DeleteCharacterInfoMessage Message;

	FCharacterInfo* CharacterInfo = m_CharacterInfoMap.Find(m_SelectJob);
	Message.m_CharacterInfo = *CharacterInfo;

	GameServerSerializer Serializer;
	Message.Serialize(Serializer);

	if (!GameInst->Send(Serializer.GetData()))
	{
		PrintViewport(2.f, FColor::Red, TEXT("DeleteCharacterInfoMessage Send Error!"));
	}
	//--------------------------------------------------------------------------------------
}

void UDeleteCheckWidget::CloseButtonClicked()
{

}