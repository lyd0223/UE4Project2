
#pragma once

#include "../../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ListView.h"
#include "ChatWidget.generated.h"

UCLASS()
class PROJECT1_API UChatWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UEditableTextBox* m_ChatEditableText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UListView* m_ChatListView;

	
	protected:
	virtual void NativeConstruct() override;
	
	public:
	UFUNCTION()
	void OnChatTextChanged(const FText& _Text, ETextCommit::Type _CommitType);
	UFUNCTION()
	void AddItemChatListView(const FString& _NickName, const FString& _Chat);
};
