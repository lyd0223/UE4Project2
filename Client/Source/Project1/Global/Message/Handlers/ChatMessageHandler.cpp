#include "ChatMessageHandler.h"

#include "Kismet/GameplayStatics.h"
#include "Project1/WaitingRoomGameModeBase.h"
#include "Project1/UI/WaitingRoomLevel/WaitingRoomMainWidget.h"
#include "Project1/UI/WaitingRoomLevel/Chat/ChatWidget.h"

void ChatMessageHandler::Start()
{
	AWaitingRoomGameModeBase* GameMode = Cast<AWaitingRoomGameModeBase>(m_World->GetAuthGameMode());
	if(GameMode ==nullptr)
		return;
	UWaitingRoomMainWidget* WaitingRoomMainWidget = Cast<UWaitingRoomMainWidget>(GameMode->GetMainWidget());
	if(WaitingRoomMainWidget == nullptr)
		return;
	UChatWidget* ChatWidget = WaitingRoomMainWidget->GetChatWidget();
	if(ChatWidget == nullptr)
		return;
	FString NickNameString = TEXT("");
	UClientBlueprintFunctionLibrary::UTF8ToFString(m_Message->m_NickName, NickNameString);
	FString ChatString = TEXT("");
	UClientBlueprintFunctionLibrary::UTF8ToFString(m_Message->m_Chat, ChatString);
	ChatWidget->AddItemChatListView(NickNameString, ChatString);
}
