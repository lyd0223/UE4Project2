#include "ChatMessageHandler.h"

#include "Kismet/GameplayStatics.h"
#include "Project1/WaitingRoomGameModeBase.h"
#include "Project1/UI/WaitingRoomLevel/WaitingRoomMainWidget.h"
#include "Project1/UI/WaitingRoomLevel/Chat/ChatWidget.h"


ChatMessageHandler::ChatMessageHandler(std::shared_ptr<ChatMessage> _ChatMessage)
{
	m_GameInstance = nullptr;
	m_World = nullptr;
	m_ChatMessage = _ChatMessage;
}

void ChatMessageHandler::Init(UProject1GameInstance* _GameInstance, UWorld* _World)
{
	m_GameInstance = _GameInstance;
	m_World = _World;
}

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
	UClientBlueprintFunctionLibrary::UTF8ToFString(m_ChatMessage->m_NickName, NickNameString);
	FString ChatString = TEXT("");
	UClientBlueprintFunctionLibrary::UTF8ToFString(m_ChatMessage->m_Chat, ChatString);
	ChatWidget->AddItemChatListView(NickNameString, ChatString);
}
