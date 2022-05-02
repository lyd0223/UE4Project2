#pragma once

#include "../../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "DeleteCheckWidget.generated.h"

UCLASS()
class PROJECT1_API UDeleteCheckWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_DeleteButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* m_CloseButton;

	UPROPERTY()
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
	void DeleteButtonClicked();

	UFUNCTION()
	void CloseButtonClicked();
};
