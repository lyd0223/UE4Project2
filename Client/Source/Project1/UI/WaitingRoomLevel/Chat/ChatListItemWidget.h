
#pragma once

#include "../../../GameInfo.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ChatListItemWidget.generated.h"

UCLASS()
class PROJECT1_API UChatListItemWidget : public UUserWidget , public IUserObjectListEntry
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_ChatTextBlock;
	
	protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	public:
	void SetChatTextBlock(const FString& Text)
	{
		m_ChatTextBlock->SetText(FText::FromString(Text));
	}
	

	
};
