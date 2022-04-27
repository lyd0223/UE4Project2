#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ClearWidget.generated.h"

UCLASS()
class PROJECT1_API UClearWidget : public UUserWidget
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY()
	UButton* m_RetryButton;
	UPROPERTY()
	UButton* m_WaitingRoomButton;

	protected:
	virtual void NativeConstruct() override;

	public:
	UFUNCTION()
	void RetryButtonClicked();
	UFUNCTION()
	void WaitingRoomButtonClicked();
};
