// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatListItemWidget.h"

#include "ChatListItemData.h"


void UChatListItemWidget::NativeConstruct()
{
	m_ChatTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ChatTextBlock")));
}


void UChatListItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UChatListItemData* ListItem = Cast<UChatListItemData>(ListItemObject);

	ListItem->SetOwnerItemWidget(this);
	
	FString NickNameString = ListItem->GetNickNameString();
	FString ChatString = ListItem->GetChatString();

	FString ResultString = FString::Printf(TEXT("%s : %s"), *NickNameString, *ChatString);

	m_ChatTextBlock->SetText(FText::FromString(ResultString));
}
