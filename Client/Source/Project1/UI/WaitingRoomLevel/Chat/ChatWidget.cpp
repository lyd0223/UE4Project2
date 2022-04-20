
#include "ChatWidget.h"

#include "ChatListItemData.h"
#include "ChatListItemWidget.h"
#include "MaterialEditor/DEditorTextureParameterValue.h"
#include "Project1/Project1GameInstance.h"
#include "Project1/Global/Message/ServerAndClient.h"


void UChatWidget::NativeConstruct()
{
	m_ChatEditableText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ChatEditableText")));
	m_ChatListView = Cast<UListView>(GetWidgetFromName(TEXT("ChatListView")));

	m_ChatEditableText->OnTextCommitted.AddDynamic(this, &UChatWidget::OnChatTextChanged);
}


void UChatWidget::OnChatTextChanged(const FText& _Text, ETextCommit::Type _CommitType)
{
	m_ChatEditableText->SetText(FText::FromString(TEXT("")));
	if(_CommitType != ETextCommit::Type::OnEnter)
		return;
	
	//서버로 채팅 패킷 보내기.--------------------------------------------------------
	UProject1GameInstance* GameInst = Cast<UProject1GameInstance>(GetGameInstance());
	if(GameInst == nullptr)
		return;
	if(GameInst->GetIsClientMode())
		return;		
	ChatMessage Message;

	//메시지에 닉네임 담기
	Message.m_NickName = GameInst->GetPlayingCharacterInfo().m_Nickname;
	//메시지에 채팅 담기
	FString ChatString = _Text.ToString();
	UClientBlueprintFunctionLibrary::FStringToUTF8(ChatString,Message.m_Chat);
	
	GameServerSerializer Serializer;
	Message.Serialize(Serializer);
	
	if (!GameInst->Send(Serializer.GetData()))
	{
		PrintViewport(2.f, FColor::Red, TEXT("SignUp Message Send Error!"));
	}
	//--------------------------------------------------------------------------------------
	
}
void UChatWidget::AddItemChatListView(const FString& _NickName, const FString& _Chat)
{
	//ItemData 설정.
	UChatListItemData* ItemData = NewObject<UChatListItemData>(this, UChatListItemData::StaticClass());
	UProject1GameInstance* GameInstance = Cast<UProject1GameInstance>(GetWorld()->GetGameInstance());
	if(GameInstance == nullptr)
		return;
	ItemData->SetNickNameString(_NickName);
	ItemData->SetChatString(_Chat);
	m_ChatListView->AddItem(ItemData);
	
	//ChatListView 사이즈 커지면 위에부터 삭제.
	if(m_ChatListView->GetNumItems() > 20)
	{
		m_ChatListView->RemoveItem(m_ChatListView->GetItemAt(0));
	}
}