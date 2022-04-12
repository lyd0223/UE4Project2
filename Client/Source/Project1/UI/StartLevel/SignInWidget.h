#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "SignInWidget.generated.h"

UCLASS()
class PROJECT1_API USignInWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UButton* m_SignInButton;
	UPROPERTY()
	UButton* m_CloseButton;

	UPROPERTY()
	UEditableTextBox* m_IDTextBox;
	UPROPERTY()
	UEditableTextBox* m_PWTextBox;

	FString m_IDString;
	FString m_PWString;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void SignInButtonClicked();
	UFUNCTION()
	void CloseButtonClicked();

	UFUNCTION()
	void IDTextBoxChanged(const FText& Text);
	UFUNCTION()
	void PWTextBoxChanged(const FText& Text);
};
