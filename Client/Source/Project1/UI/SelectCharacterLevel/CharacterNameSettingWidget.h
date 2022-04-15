#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "CharacterNameSettingWidget.generated.h"

UCLASS()
class PROJECT1_API UCharacterNameSettingWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UButton* m_CreateButton;
	UPROPERTY()
	UButton* m_CloseButton;

	UPROPERTY()
	UEditableTextBox* m_NameTextBox;

	FString m_NameString;

	class USelectCharacterMainWidget* m_OwnerWidget;

public:
	void SetOwnerWidget(class USelectCharacterMainWidget* _OwnerWidget)
	{
		m_OwnerWidget = _OwnerWidget;
	}
	
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void CreateButtonClicked();
	UFUNCTION()
	void CloseButtonClicked();

	UFUNCTION()
	void NameTextBoxChanged(const FText& Text);
};
