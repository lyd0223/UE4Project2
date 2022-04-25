#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CharacterNicknameWidget.generated.h"

DECLARE_DELEGATE(FSetNicknameDeligate);
UCLASS()
class PROJECT1_API UCharacterNicknameWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_NicknameText;

	FSetNicknameDeligate m_SetNicknameDeligate;

	
	protected:
	virtual void NativeConstruct() override;

	public:
	void SetNicknameText(const FString& _Text)
	{
		m_NicknameText->SetText(FText::FromString(_Text));
	}
	
	template <class T>
	void SetDelegate(T* _Obj, void(T::* _Func)())
	{
		m_SetNicknameDeligate.BindUObject(_Obj, _Func);
	}
};
