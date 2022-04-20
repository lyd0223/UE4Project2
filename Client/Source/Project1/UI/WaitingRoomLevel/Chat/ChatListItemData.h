
#pragma once

#include "../../../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "ChatListItemData.generated.h"

UCLASS()
class PROJECT1_API UChatListItemData : public UObject
{
	GENERATED_BODY()

	public:
	UChatListItemData();

	protected:
	FString m_NickNameString;
	FString m_ChatString;

	class UChatListItemWidget* m_OwnerItemWidget;
	
	public:
	void SetNickNameString(const FString& _NickNameString)
	{
		m_NickNameString =_NickNameString;
	}
	FString GetNickNameString() const
	{
		return m_NickNameString;
	}
	void SetChatString(const FString& _ChatString)
	{
		m_ChatString = _ChatString;
	}
	FString GetChatString() const
	{
		return m_ChatString;
	}
	
	
	void SetOwnerItemWidget(class UChatListItemWidget* ItemWidget)
	{
		m_OwnerItemWidget = ItemWidget;
	}
	UChatListItemWidget* GetOwnerItemWidget() const
	{
		return m_OwnerItemWidget;
	}
};
